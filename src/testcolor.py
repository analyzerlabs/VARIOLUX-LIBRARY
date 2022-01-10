import sys
from PyQt5 import QtGui, QtCore

class QHighlightSquareWidget (QtGui.QWidget):
    def __init__ (self, parent = None):
        QtGui.QWidget.__init__(self, parent = None)
        self.setSizePolicy (
            QtGui.QSizePolicy (
                QtGui.QSizePolicy.Expanding,
                QtGui.QSizePolicy.Expanding))
        self.setMinimumSize(self.minimumSizeHint())
        allQGridLayout = QtGui.QGridLayout()
        allQGridLayout.addItem(QtGui.QSpacerItem(10,10), 0, 0)
        allQGridLayout.addItem(QtGui.QSpacerItem(10,10), 0, 1)
        allQGridLayout.addItem(QtGui.QSpacerItem(10,10), 1, 0)
        allQGridLayout.addItem(QtGui.QSpacerItem(10,10), 1, 1)       
        self.setLayout(allQGridLayout)
        self.resize(150, 150)
        self.update()

    def paintEvent (self, eventQPaintEvent):
        myQPainter = QtGui.QPainter(self)
        myQPainter.setRenderHint(QtGui.QPainter.Antialiasing)
        winHeight = self.size().height()
        heightStep = winHeight / 2
        winWidth  = self.size().width()
        widthStep = winWidth / 2

        myQPainter.setPen(QtCore.Qt.black)
        for i in range(4):
            myQPainter.drawLine(QtCore.QPoint(i * widthStep, 0             ), QtCore.QPoint(i * widthStep, winHeight     ))
            myQPainter.drawLine(QtCore.QPoint(0,             heightStep * i), QtCore.QPoint(winWidth,      heightStep * i))

        highlightCoordinate = (1, 1)
        myQPen = QtGui.QPen(QtCore.Qt.blue, 3)        
        myQPainter.setPen(myQPen)
        coordHighlight = [
            QtCore.QPoint( highlightCoordinate[0]      * widthStep,  highlightCoordinate[1]      * heightStep),
            QtCore.QPoint((highlightCoordinate[0] + 1) * widthStep,  highlightCoordinate[1]      * heightStep),
            QtCore.QPoint((highlightCoordinate[0] + 1) * widthStep, (highlightCoordinate[1] + 1) * heightStep),
            QtCore.QPoint( highlightCoordinate[0]      * widthStep, (highlightCoordinate[1] + 1) * heightStep),
            QtCore.QPoint( highlightCoordinate[0]      * widthStep,  highlightCoordinate[1]      * heightStep)]
        myQPainter.drawPolyline(*coordHighlight)

    def minimumSizeHint (self):
        return QtCore.QSize(120, 120)

if __name__=="__main__":
    myQApplication = QtGui.QApplication(sys.argv)
    myQHighlightSquareWidget = QHighlightSquareWidget()
    myQHighlightSquareWidget.show()
    sys.exit(myQApplication.exec_())