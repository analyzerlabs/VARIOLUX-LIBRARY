from main_window_ui import *

class MainWindow(QtWidgets.QMainWindow, Ui_MainWindow):
    pass

if __name__ == "__main__":
    app = QtWidgets.QApplication([])
    window = MainWindow()
    window.show()
    app.exec_()