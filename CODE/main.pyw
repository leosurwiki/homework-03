# -*- coding: utf-8 -*-

"""
Module implementing main_GUI.
"""

from PyQt4.QtGui import * 
from PyQt4.QtCore import *
import sys
from Ui_main import Ui_main_GUI
class main_GUI(QDialog, Ui_main_GUI):
    """
    Class documentation goes here.
    """
    t = {}
    l = {}
    now = 0
    def matrixinput(self,main_GUI):
        result = []
        for i in range(32):
            tmp = []
            for j in range(32): 
                try:
                    tmp.append(self.t[self.now].item(i,j).text())
                except:
                    tmp.append('0')
            result.append(tmp)
        m=0
        n=0 #整张表为空时表示矩阵[0]
        for i in range(32):
            for j in range(32): 
                try:
                    result[i][j] = int(result[i][j])
                except:
                    return 1
                if result[i][j] < -100 or result[i][j]  > 100:
                    return 2
                if result[i][j]!=0 and (i>n):
                    n=i
                if result[i][j]!=0 and (j>m):
                    m=j
        matrix = []
        for i in range(n+1):
            for j in range(m+1):
                matrix.append(result[i][j])
        return [n+1,m+1,matrix]
    def solve(self,n,m,c,a,h,v):
        import os
        import ctypes
        from ctypes import c_int
        lib_handleO = ctypes.cdll.LoadLibrary('./bin/original.dll')
        lib_handleA = ctypes.cdll.LoadLibrary('./bin/atype.dll')
        ans = 0
        tmp = (c_int*(n*m))()
        for i in range(n*m):
            tmp[i] = c[i]
        ans = 0
        if a==True :
            ans = lib_handleA.deal(n,m,tmp,v,h)
        else:
            ans = lib_handleO.maxsumblock(tmp,n,m,h,v)
        for i in range(n):
            for j in range(m):
                if int(tmp[i*m+j]) == -10001:
                    nitem = self.t[self.now].item(i,j)
                    if nitem==None:
                        nitem = QTableWidgetItem ('0')
                    nitem.setBackgroundColor(QColor(255,215,0))
                    self.t[self.now].setItem(i,j,nitem)
        self.l[self.now].setText('ans:'+str(ans))
            
    def __init__(self, parent = None):
        """
        Constructor
        """
        QDialog.__init__(self, parent)
        self.setupUi(self)
        self.t[0] = self.tableWidget
        self.t[1] = self.tableWidget_2
        self.l[0] = self.label
        self.l[1] = self.label_2
    @pyqtSignature("")
    def on_pushButton_clicked(self):
        """
        Slot documentation goes here.
        """

        amorphous = self.checkBox_2.isChecked()
        horizontal = self.checkBox.isChecked()
        vertical = self.checkBox_3.isChecked()
        self.now = int(self.tabWidget.currentIndex())
        if (self.matrixinput(self)==1):
            self.l[self.now].setText("Please input numbers in the table.")
            self.t[self.now].setDisabled(True)
            return 0
        if (self.matrixinput(self)==2):
            self.l[self.now].setText("Please input numbers in range(-100,100) in the table.")
            self.t[self.now].setDisabled(True)
            return 0
        else:
            [n,m,matrix] = self.matrixinput(self)
        self.solve(n,m,matrix,amorphous,horizontal,vertical)
        self.t[self.now].setCurrentCell(32,32)
        
        # TODO: not implemented yet
    @pyqtSignature("")
    def on_pushButton_2_clicked(self):
        """
        Slot documentation goes here.
        """
        # TODO: not implemented yet
        
        for i in range(32):
            for j in range(32):
                self.t[self.now].setItem(i,j,None)
        self.t[self.now].setDisabled(False)  
        self.pushButton.setDisabled(False)
        self.l[self.now].setText("")
app = QApplication(sys.argv)  
window = main_GUI()  
window.show()  
app.exec_()  
    

