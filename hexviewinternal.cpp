
#include <QPainter>

#include "hexviewinternal.h"
#include "globalsettings.h"

namespace
{
    static const uint rowInitialStart = 10;
}


HexViewInternal::HexViewInternal(QByteArray *data, QWidget *parent)
    : QScrollArea(parent)
    , data(data)
    , selectStart(0)
    , selectStop(0)
    , selectedOffset(0)
    , byteSelected(false)
{
    this->setObjectName("HEXVIEW");

    this->setFont(GlobalSettings::instance().hexviewFont());

    QScrollArea::setFont(this->font());
    QFontMetrics metrics(this->font());

    fontWidth  = metrics.averageCharWidth() + metrics.averageCharWidth() / 2 ;
    fontHeight = metrics.height();

    rowCount = data->size() / bytesPerRow();
}

int HexViewInternal::offsetAreaWidth()    const { return 10 * fontWidth; }

int HexViewInternal::hexviewAreaWidth()   const { return bytesPerRow() * 2 * fontWidth; }

int HexViewInternal::asciiviewAreaWidth() const { return bytesPerRow() * fontWidth; }

int HexViewInternal::offsetAreaStart()    const { return 0; }

int HexViewInternal::hexviewAreaStart()   const { return offsetAreaStart() + offsetAreaWidth() + (fontWidth / 2); }

int HexViewInternal::asciiviewAreaStart() const { return hexviewAreaStart() + hexviewAreaWidth() + fontWidth; }

void HexViewInternal::drawViews(QPainter &painter, int offset, int row, int bytesPerRow) const
{
    if (offset < data->size())
    {
        // Draw the offset area

        QString string = QString("0x") + QString("%1").arg((uint)((offset / bytesPerRow) * bytesPerRow), 8, 16, QChar('0')).toUpper();

        painter.setPen(GlobalSettings::instance().hexviewOffsetColor());
        painter.drawText(offsetAreaStart(), row, string.length() * fontWidth, fontHeight, Qt::AlignCenter, string);

        for (int i = 0, index = offset; i < bytesPerRow && index < data->size(); ++i, ++index)
        {
            QRect border(hexviewAreaStart() + (i * 2 * fontWidth), row, 2 * fontWidth, fontHeight);

            unsigned char symbol = data->at( index );

            // Draw the hex view

            string = QString("%1").arg((uint)symbol, 2, 16, QChar('0'));

            // Draw the selection. Determine the direction of the selection first.

            int start = selectStop > selectStart ? selectStart : selectStop;
            int stop  = selectStop > selectStart ? selectStop  : selectStart;

            if (byteSelected && (index >= start && index <= stop))
            {
                // Draw the selection

                painter.fillRect(border, GlobalSettings::instance().hexviewSelectionBack());
                painter.setPen(GlobalSettings::instance().hexviewSelectionFront());
            }
            else
            {
                painter.setPen(GlobalSettings::instance().hexviewColor());
            }

            painter.drawText(border, Qt::AlignCenter, string);

            // Draw the ASCII view

            string.clear();

            painter.setPen(GlobalSettings::instance().hexviewAsciiColor());

            if (0x0d == symbol || 0x0a == symbol || 0x00 == symbol)
                string = '.';
            else
                string = symbol;

            painter.drawText(asciiviewAreaStart() + (i * fontWidth),
                             row, string.length() * fontWidth, fontHeight, Qt::AlignCenter, string);
        }
    }
}

void HexViewInternal::updateScrollbars()
{
    const unsigned int totallines   = data->size() / bytesPerRow() + 5;
    const unsigned int visiblelines = viewport()->height() / fontHeight;
    unsigned       int scrollmax    = (totallines > visiblelines) ? totallines - visiblelines : 0;

    this->verticalScrollBar()->setMaximum(scrollmax);
}

int HexViewInternal::bytesPerRow() const
{
    unsigned int num = (viewport()->width() - offsetAreaWidth() - (2 * (fontWidth / 2))) / (fontWidth * 3);
    return num == 0 ? 1 : num;
}

void HexViewInternal::resizeEvent( QResizeEvent *event )
{
    updateScrollbars();
}

void HexViewInternal::repaint()
{
    viewport()->repaint();
}

void HexViewInternal::scrollContentsBy( int dx, int dy )
{
    viewport()->repaint();
}

void HexViewInternal::paintEvent(QPaintEvent *)
{
    int bpr = bytesPerRow();

    rowCount = data->size() / bpr;

    QPainter painter(viewport());

    // Pixel offset of this row
    unsigned int row = rowInitialStart;

    // Current offset
    unsigned int offset = verticalScrollBar()->value() * bpr;

    while( row + fontHeight < static_cast<unsigned int>(height()) && offset < static_cast<unsigned int>( data->size() ) )
    {
        drawViews(painter, offset, row, bpr);
        offset += bpr;
        row    += fontHeight;
    }
}

void HexViewInternal::selectionStart(int x, int y)
{
    int offset = getOffset(x, y);

    selectStart = offset;
    selectStop  = offset;
}

void HexViewInternal::selectionUpdate(int x, int y)
{
    int offset = getOffset(x, y);

    selectStop = offset;

    repaint();
}

int HexViewInternal::getOffset(int x, int y) const
{
    // Calculate the offset of the selection start

    x = ((x - hexviewAreaStart()) / 2) * 2;

    uint row = (y - rowInitialStart) / fontHeight;
    uint tooffset = verticalScrollBar()->value() * bytesPerRow() + row * bytesPerRow() + ( x / (fontWidth * 2) );

    if (tooffset >= data->size())
        return 0;

    return tooffset;
}

bool HexViewInternal::isInHexViewArea(int x) const
{
    return x > hexviewAreaStart() && x < (asciiviewAreaStart() - (fontWidth / 2));
}

void HexViewInternal::leftButtonPressed(int x, int y)
{
    int offset = getOffset(x, y);

    // Update the offset

    emit signal_updateOffset(offset);

    byteSelected = true;

    selectionStart(x, y);

    repaint();
}

void HexViewInternal::rightButtonPressed(int x, int y)
{
    int offset = getOffset(x, y);
    int start  = selectStop > selectStart ? selectStart : selectStop;
    int stop   = selectStop > selectStart ? selectStop  : selectStart;

    // Update the offset

    if (byteSelected && offset >= start && offset <= stop)
    {
    }
    else
    {
        byteSelected = true;

        selectionStart(x, y);

        repaint();
    }

    // Show a menu
}

void HexViewInternal::mousePressEvent(QMouseEvent *event)
{
    pressedMouseButton = event->button();

    if (isInHexViewArea(event->x()))
    {
        if (pressedMouseButton == Qt::LeftButton)
        {
            leftButtonPressed(event->x(), event->y());
        }
        else if (pressedMouseButton == Qt::RightButton)
        {
            rightButtonPressed(event->x(), event->y());
        }
    }
    else
    {
        // Clear any previous selection

        byteSelected = false;
        repaint();
    }
}

void HexViewInternal::mouseMoveEvent(QMouseEvent *event)
{
    if (pressedMouseButton == Qt::LeftButton)
    {
        selectionUpdate(event->x(), event->y());
    }
}

void HexViewInternal::mouseReleaseEvent(QMouseEvent *event)
{
}

HexViewInternal::~HexViewInternal()
{
    delete data;
}
