
#ifndef HEXVIEWINTERNAL_H
#define HEXVIEWINTERNAL_H

#include <QResizeEvent>
#include <QScrollArea>
#include <QScrollBar>
#include <QByteArray>
#include <QWidget>


class HexViewInternal : public QScrollArea
{
    Q_OBJECT

public:

    HexViewInternal(QByteArray *data, QWidget *parent = 0);
    ~HexViewInternal();

signals:

    void signal_updateOffset(int);

protected:

    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);
    void scrollContentsBy(int, int);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:

    void repaint();
    void updateScrollbars();

private:

    int   offsetAreaStart()    const;
    int   offsetAreaWidth()    const;
    int   hexviewAreaStart()   const;
    int   hexviewAreaWidth()   const;
    int   asciiviewAreaStart() const;
    int   asciiviewAreaWidth() const;
    int   bytesPerRow()        const;
    int   getOffset(int, int)  const;

    void  drawViews(QPainter &painter, int offset, int row, int bytesPerRow) const;

    void  leftButtonPressed (int x, int y);
    void  rightButtonPressed(int x, int y);
    void  selectionUpdate(int, int);
    void  selectionStart(int, int);

    bool  isInHexViewArea(int x) const;

private:

    /**
     * Data to be shown in the hexview
     */
    const QByteArray *data;

    int  fontWidth;
    int  fontHeight;
    int  rowCount;
    int  selectStart;
    int  selectStop;
    int  selectedOffset;

    bool byteSelected;

    Qt::MouseButton pressedMouseButton;
};

#endif /* HEXVIEWINTERNAL_H */
