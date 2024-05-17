import sys
from PyQt5 import uic, QtWidgets, QtCore
import serial
import serial.tools.list_ports

qtCreatorFile = "r2.ui"  # Nombre del archivo aqui
Ui_MainWindow, QtBaseClass = uic.loadUiType(qtCreatorFile)


class MyApp(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self):
        QtWidgets.QMainWindow.__init__(self)
        Ui_MainWindow.__init__(self)
        self.setupUi(self)
        self.timer = QtCore.QTimer()
        self.timer.timeout.connect(self.leerDatos)
        self.arduino = None
        self.BtnConectar.clicked.connect(self.conectarArduino)
        self.servomotor.valueChanged.connect(self.enviarDatos)


    def conectarArduino(self):
        ports = serial.tools.list_ports.comports()
        for port in ports:
            if "Arduino" in port.description:
                self.arduino = serial.Serial(port.device, 9600)
                if self.arduino.is_open:
                    self.statusBar().showMessage(f"Conectado Arduino en puerto: {port.device}")
                    self.timer.start(100)
                print("Arduino no encontrado")

    def enviarDatos(self):
        servo = self.servomotor.value()
        self.arduino.write(str(servo).encode())
    def leerDatos(self):
        if self.arduino is not None and self.arduino.in_waiting > 0:
            dist = int(self.arduino.readline().decode().strip())
            self.distancia.setText(str(dist))
            print(dist)

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    window = MyApp()
    window.show()
    sys.exit(app.exec_())