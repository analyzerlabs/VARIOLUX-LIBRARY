# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'GUI.ui'
#
# Created by: PyQt5 UI code generator 5.15.6
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from abc import abstractproperty
from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(965, 795)
        self.scrollArea = QtWidgets.QScrollArea(Dialog)
        self.scrollArea.setGeometry(QtCore.QRect(180, 60, 591, 61))
        self.scrollArea.setWidgetResizable(True)
        self.scrollArea.setObjectName("scrollArea")
        self.scrollAreaWidgetContents = QtWidgets.QWidget()
        self.scrollAreaWidgetContents.setGeometry(QtCore.QRect(0, 0, 589, 59))
        self.scrollAreaWidgetContents.setObjectName("scrollAreaWidgetContents")
        self.Color_2 = QtWidgets.QLabel(self.scrollAreaWidgetContents)
        self.Color_2.setEnabled(True)
        self.Color_2.setGeometry(QtCore.QRect(50, 20, 71, 21))
        self.Color_2.setObjectName("Color_2")
        self.ColorPicker = QtWidgets.QPushButton(self.scrollAreaWidgetContents)
        self.ColorPicker.setGeometry(QtCore.QRect(460, 20, 91, 23))
        self.ColorPicker.setObjectName("ColorPicker")
        self.RedColor_2 = QtWidgets.QLineEdit(self.scrollAreaWidgetContents)
        self.RedColor_2.setGeometry(QtCore.QRect(130, 20, 81, 20))
        self.RedColor_2.setObjectName("RedColor_2")
        self.GreenColor = QtWidgets.QLineEdit(self.scrollAreaWidgetContents)
        self.GreenColor.setGeometry(QtCore.QRect(230, 20, 81, 20))
        self.GreenColor.setClearButtonEnabled(False)
        self.GreenColor.setObjectName("GreenColor")
        self.BlueColor = QtWidgets.QLineEdit(self.scrollAreaWidgetContents)
        self.BlueColor.setGeometry(QtCore.QRect(330, 20, 81, 20))
        self.BlueColor.setObjectName("BlueColor")
        self.scrollArea.setWidget(self.scrollAreaWidgetContents)
        self.buttonBox = QtWidgets.QDialogButtonBox(Dialog)
        self.buttonBox.setGeometry(QtCore.QRect(150, 690, 711, 51))
        self.buttonBox.setOrientation(QtCore.Qt.Horizontal)
        self.buttonBox.setStandardButtons(QtWidgets.QDialogButtonBox.Cancel|QtWidgets.QDialogButtonBox.Ok)
        self.buttonBox.setObjectName("buttonBox")
        self.pushButton_2 = QtWidgets.QPushButton(Dialog)
        self.pushButton_2.setGeometry(QtCore.QRect(190, 700, 75, 23))
        self.pushButton_2.setObjectName("pushButton_2")
        self.progressBar = QtWidgets.QProgressBar(Dialog)
        self.progressBar.setGeometry(QtCore.QRect(90, 730, 211, 23))
        self.progressBar.setProperty("value", 24)
        self.progressBar.setObjectName("progressBar")
        self.listWidget = QtWidgets.QListWidget(Dialog)
        self.listWidget.setGeometry(QtCore.QRect(90, 700, 81, 21))
        self.listWidget.setAlternatingRowColors(False)
        self.listWidget.setObjectName("listWidget")
        self.scrollArea_2 = QtWidgets.QScrollArea(Dialog)
        self.scrollArea_2.setGeometry(QtCore.QRect(180, 120, 591, 61))
        self.scrollArea_2.setWidgetResizable(True)
        self.scrollArea_2.setObjectName("scrollArea_2")
        self.scrollAreaWidgetContents_2 = QtWidgets.QWidget()
        self.scrollAreaWidgetContents_2.setGeometry(QtCore.QRect(0, 0, 589, 59))
        self.scrollAreaWidgetContents_2.setObjectName("scrollAreaWidgetContents_2")
        self.Color_3 = QtWidgets.QLabel(self.scrollAreaWidgetContents_2)
        self.Color_3.setEnabled(True)
        self.Color_3.setGeometry(QtCore.QRect(50, 20, 71, 21))
        self.Color_3.setObjectName("Color_3")
        self.ColorPicker_2 = QtWidgets.QPushButton(self.scrollAreaWidgetContents_2)
        self.ColorPicker_2.setGeometry(QtCore.QRect(460, 20, 91, 23))
        self.ColorPicker_2.setObjectName("ColorPicker_2")
        self.RedColor_3 = QtWidgets.QLineEdit(self.scrollAreaWidgetContents_2)
        self.RedColor_3.setGeometry(QtCore.QRect(130, 20, 81, 20))
        self.RedColor_3.setObjectName("RedColor_3")
        self.GreenColor_2 = QtWidgets.QLineEdit(self.scrollAreaWidgetContents_2)
        self.GreenColor_2.setGeometry(QtCore.QRect(230, 20, 81, 20))
        self.GreenColor_2.setClearButtonEnabled(False)
        self.GreenColor_2.setObjectName("GreenColor_2")
        self.BlueColor_2 = QtWidgets.QLineEdit(self.scrollAreaWidgetContents_2)
        self.BlueColor_2.setGeometry(QtCore.QRect(330, 20, 81, 20))
        self.BlueColor_2.setObjectName("BlueColor_2")
        self.scrollArea_2.setWidget(self.scrollAreaWidgetContents_2)
        self.scrollArea_3 = QtWidgets.QScrollArea(Dialog)
        self.scrollArea_3.setGeometry(QtCore.QRect(180, 180, 591, 61))
        self.scrollArea_3.setWidgetResizable(True)
        self.scrollArea_3.setObjectName("scrollArea_3")
        self.scrollAreaWidgetContents_3 = QtWidgets.QWidget()
        self.scrollAreaWidgetContents_3.setGeometry(QtCore.QRect(0, 0, 589, 59))
        self.scrollAreaWidgetContents_3.setObjectName("scrollAreaWidgetContents_3")
        self.Color_4 = QtWidgets.QLabel(self.scrollAreaWidgetContents_3)
        self.Color_4.setEnabled(True)
        self.Color_4.setGeometry(QtCore.QRect(50, 20, 71, 21))
        self.Color_4.setObjectName("Color_4")
        self.ColorPicker_3 = QtWidgets.QPushButton(self.scrollAreaWidgetContents_3)
        self.ColorPicker_3.setGeometry(QtCore.QRect(460, 20, 91, 23))
        self.ColorPicker_3.setObjectName("ColorPicker_3")
        self.RedColor_4 = QtWidgets.QLineEdit(self.scrollAreaWidgetContents_3)
        self.RedColor_4.setGeometry(QtCore.QRect(130, 20, 81, 20))
        self.RedColor_4.setObjectName("RedColor_4")
        self.GreenColor_3 = QtWidgets.QLineEdit(self.scrollAreaWidgetContents_3)
        self.GreenColor_3.setGeometry(QtCore.QRect(230, 20, 81, 20))
        self.GreenColor_3.setClearButtonEnabled(False)
        self.GreenColor_3.setObjectName("GreenColor_3")
        self.BlueColor_3 = QtWidgets.QLineEdit(self.scrollAreaWidgetContents_3)
        self.BlueColor_3.setGeometry(QtCore.QRect(330, 20, 81, 20))
        self.BlueColor_3.setObjectName("BlueColor_3")
        self.scrollArea_3.setWidget(self.scrollAreaWidgetContents_3)
        self.scrollArea_4 = QtWidgets.QScrollArea(Dialog)
        self.scrollArea_4.setGeometry(QtCore.QRect(180, 240, 591, 61))
        self.scrollArea_4.setWidgetResizable(True)
        self.scrollArea_4.setObjectName("scrollArea_4")
        self.scrollAreaWidgetContents_4 = QtWidgets.QWidget()
        self.scrollAreaWidgetContents_4.setGeometry(QtCore.QRect(0, 0, 589, 59))
        self.scrollAreaWidgetContents_4.setObjectName("scrollAreaWidgetContents_4")
        self.Color_5 = QtWidgets.QLabel(self.scrollAreaWidgetContents_4)
        self.Color_5.setEnabled(True)
        self.Color_5.setGeometry(QtCore.QRect(50, 20, 71, 21))
        self.Color_5.setObjectName("Color_5")
        self.ColorPicker_4 = QtWidgets.QPushButton(self.scrollAreaWidgetContents_4)
        self.ColorPicker_4.setGeometry(QtCore.QRect(460, 20, 91, 23))
        self.ColorPicker_4.setObjectName("ColorPicker_4")
        self.RedColor_5 = QtWidgets.QLineEdit(self.scrollAreaWidgetContents_4)
        self.RedColor_5.setGeometry(QtCore.QRect(130, 20, 81, 20))
        self.RedColor_5.setObjectName("RedColor_5")
        self.GreenColor_4 = QtWidgets.QLineEdit(self.scrollAreaWidgetContents_4)
        self.GreenColor_4.setGeometry(QtCore.QRect(230, 20, 81, 20))
        self.GreenColor_4.setClearButtonEnabled(False)
        self.GreenColor_4.setObjectName("GreenColor_4")
        self.BlueColor_4 = QtWidgets.QLineEdit(self.scrollAreaWidgetContents_4)
        self.BlueColor_4.setGeometry(QtCore.QRect(330, 20, 81, 20))
        self.BlueColor_4.setObjectName("BlueColor_4")
        self.scrollArea_4.setWidget(self.scrollAreaWidgetContents_4)

        self.retranslateUi(Dialog)
        self.buttonBox.accepted.connect(Dialog.accept) # type: ignore
        self.buttonBox.rejected.connect(Dialog.reject) # type: ignore
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", "Dialog"))
        self.Color_2.setText(_translate("Dialog", "COLOR 1"))
        self.ColorPicker.setText(_translate("Dialog", "Color"))
        self.pushButton_2.setText(_translate("Dialog", "PushButton"))
        self.listWidget.setSortingEnabled(False)
        self.Color_3.setText(_translate("Dialog", "COLOR 1"))
        self.ColorPicker_2.setText(_translate("Dialog", "Color"))
        self.Color_4.setText(_translate("Dialog", "COLOR 1"))
        self.ColorPicker_3.setText(_translate("Dialog", "Color"))
        self.Color_5.setText(_translate("Dialog", "COLOR 1"))
        self.ColorPicker_4.setText(_translate("Dialog", "Color"))


