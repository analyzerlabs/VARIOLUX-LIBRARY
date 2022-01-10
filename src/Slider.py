# pythonprogramminglanguage.com
import sys
from PyQt5.QtCore import QRect, Qt
from PyQt5.QtGui import QPainter
from PyQt5.QtWidgets import (QApplication, QCheckBox, QGridLayout, QGroupBox,
                             QMenu, QPushButton, QRadioButton, QVBoxLayout, QWidget, QSlider)
from PyQt5.QtWidgets import *
class Window(QTabWidget,QWidget):
    def __init__(self, parent=None):
        
        super(Window, self).__init__(parent)
        self.tab1 = QWidget()
        self.tab2 = QWidget()
        self.tab3 = QWidget()
        self.tab4 = QWidget()
        self.tab5 = QWidget()
        self.addTab(self.tab1,"1-30")
        self.addTab(self.tab2,"31-60")
        self.addTab(self.tab3,"61-90")
        self.addTab(self.tab4,"91-120")
        self.addTab(self.tab5,"121-150")
        self.grid1 = QGridLayout()
        self.grid2 = QGridLayout()
        self.grid3 = QGridLayout()
        self.grid4 = QGridLayout()
        self.grid5 = QGridLayout()
        for j in range (0,6):
            for i in range (1,6):
                self.grid1.addWidget(self.ColorGroup(5*j+i), j, i)
                self.grid2.addWidget(self.ColorGroup(30+5*j+i), j, i)
                self.grid3.addWidget(self.ColorGroup(60+5*j+i), j   , i)
                self.grid4.addWidget(self.ColorGroup(90+5*j+i), j   , i)
                self.grid5.addWidget(self.ColorGroup(120+5*j+i), j   , i)
        self.tab1.setLayout(self.grid1)
        self.tab2.setLayout(self.grid2)
        self.tab3.setLayout(self.grid3)
        self.tab4.setLayout(self.grid4)
        self.tab5.setLayout(self.grid5)
        self.setWindowTitle("PyQt5 Sliders")
        self.resize(1000, 800)
    
    def ColorGroup(self,number):
        groupBox = QGroupBox("Color"+str(number))

        #radio1 = QRadioButton("&Radio horizontal slider")
        self.Red = QLineEdit(self)
        self.Red.setText("0")
        self.Green = QLineEdit(self)
        self.Green.setText("0")
        self.Blue = QLineEdit(self)
        self.Blue.setText("0")
        self.ColorChoosed = QCheckBox('', self)
        self.ColorChoosed.setGeometry(200, 150, 80, 80)
        self.ColorChoosed.setStyleSheet("QCheckBox::indicator"
                               "{"
                               "background-color : rgb(self.Red[number].text(),self.Green[number].text(),self.Blue[number].text());"
                               "}")
        self.colorButton=QPushButton("Color")
        self.colorButton.clicked.connect(self.changeColor)
        self.button_id = 0

        #radio1.setChecked(True)

        vbox = QGridLayout()
        #vbox.addWidget(radio1)
        vbox.addWidget(self.Red,0,0)
        vbox.addWidget(self.Green,0,1)
        vbox.addWidget(self.Blue,0,2)
        vbox.addWidget(self.colorButton,1,0)
        vbox.addWidget(self.ColorChoosed,1,1)
        #vbox.addStretch(1)
        groupBox.setLayout(vbox)
        self.currentChanged.connect(self.qtabwidget_currentchanged) 
        return groupBox

    def changeColor(self):
        color=QColorDialog.getColor()
        pw = self.parentWidget()
        if pw is not None:
            print(pw.layout())
        print("\ndef tab_match: button_id-> {}".format(self.button_id)) 
        #self.editor.setTextColor(color)

    def qtabwidget_currentchanged(self, index):                              # +
        self.button_id = index 

if __name__ == '__main__':
    app = QApplication(sys.argv)
    clock = Window()
    clock.show()
    sys.exit(app.exec_())