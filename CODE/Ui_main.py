# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'C:\Users\Admin\_eric4\main.ui'
#
# Created: Thu Oct 10 18:19:40 2013
#      by: PyQt4 UI code generator 4.9.6
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_main_GUI(object):
    def setupUi(self, main_GUI):
        main_GUI.setObjectName(_fromUtf8("main_GUI"))
        main_GUI.setEnabled(True)
        main_GUI.resize(571, 330)
        main_GUI.setMinimumSize(QtCore.QSize(571, 330))
        main_GUI.setMaximumSize(QtCore.QSize(571, 330))
        self.pushButton = QtGui.QPushButton(main_GUI)
        self.pushButton.setGeometry(QtCore.QRect(470, 270, 75, 23))
        self.pushButton.setObjectName(_fromUtf8("pushButton"))
        self.checkBox = QtGui.QCheckBox(main_GUI)
        self.checkBox.setGeometry(QtCore.QRect(470, 130, 71, 16))
        self.checkBox.setObjectName(_fromUtf8("checkBox"))
        self.checkBox_2 = QtGui.QCheckBox(main_GUI)
        self.checkBox_2.setGeometry(QtCore.QRect(470, 90, 71, 16))
        self.checkBox_2.setObjectName(_fromUtf8("checkBox_2"))
        self.checkBox_3 = QtGui.QCheckBox(main_GUI)
        self.checkBox_3.setGeometry(QtCore.QRect(470, 110, 71, 16))
        self.checkBox_3.setObjectName(_fromUtf8("checkBox_3"))
        self.pushButton_2 = QtGui.QPushButton(main_GUI)
        self.pushButton_2.setGeometry(QtCore.QRect(470, 230, 75, 23))
        self.pushButton_2.setObjectName(_fromUtf8("pushButton_2"))
        self.tabWidget = QtGui.QTabWidget(main_GUI)
        self.tabWidget.setGeometry(QtCore.QRect(20, 30, 421, 291))
        self.tabWidget.setObjectName(_fromUtf8("tabWidget"))
        self.tab = QtGui.QWidget()
        self.tab.setObjectName(_fromUtf8("tab"))
        self.tableWidget = QtGui.QTableWidget(self.tab)
        self.tableWidget.setGeometry(QtCore.QRect(10, 10, 391, 221))
        self.tableWidget.setRowCount(32)
        self.tableWidget.setColumnCount(32)
        self.tableWidget.setObjectName(_fromUtf8("tableWidget"))
        self.label = QtGui.QLabel(self.tab)
        self.label.setGeometry(QtCore.QRect(10, 240, 401, 16))
        self.label.setText(_fromUtf8(""))
        self.label.setObjectName(_fromUtf8("label"))
        self.tabWidget.addTab(self.tab, _fromUtf8(""))
        self.tab_2 = QtGui.QWidget()
        self.tab_2.setObjectName(_fromUtf8("tab_2"))
        self.tableWidget_2 = QtGui.QTableWidget(self.tab_2)
        self.tableWidget_2.setGeometry(QtCore.QRect(10, 10, 391, 221))
        self.tableWidget_2.setRowCount(32)
        self.tableWidget_2.setColumnCount(32)
        self.tableWidget_2.setObjectName(_fromUtf8("tableWidget_2"))
        self.label_2 = QtGui.QLabel(self.tab_2)
        self.label_2.setGeometry(QtCore.QRect(10, 240, 401, 16))
        self.label_2.setText(_fromUtf8(""))
        self.label_2.setObjectName(_fromUtf8("label_2"))
        self.tabWidget.addTab(self.tab_2, _fromUtf8(""))

        self.retranslateUi(main_GUI)
        self.tabWidget.setCurrentIndex(0)
        QtCore.QMetaObject.connectSlotsByName(main_GUI)

    def retranslateUi(self, main_GUI):
        main_GUI.setWindowTitle(_translate("main_GUI", "Dialog", None))
        self.pushButton.setText(_translate("main_GUI", "OK", None))
        self.checkBox.setText(_translate("main_GUI", "Horizontal", None))
        self.checkBox_2.setText(_translate("main_GUI", "Amorphous", None))
        self.checkBox_3.setText(_translate("main_GUI", "Vertical", None))
        self.pushButton_2.setText(_translate("main_GUI", "Reset", None))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab), _translate("main_GUI", "FILE1", None))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_2), _translate("main_GUI", "FILE2", None))


if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    main_GUI = QtGui.QDialog()
    ui = Ui_main_GUI()
    ui.setupUi(main_GUI)
    main_GUI.show()
    sys.exit(app.exec_())

