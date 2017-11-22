#!/bin/python3
import gi
import serial

gi.require_version('Gtk', '3.0')
from gi.repository import Gtk

win = Gtk.Window()
win.connect("delete-event", Gtk.main_quit)
builder = Gtk.Builder()
builder.add_from_file("window.glade")
win = builder.get_object("window")

ser=serial.Serial('/dev/ttyUSB0', 9600);

def send_color(r,g,b):
    ser.write(b'4')
    ser.write(str.encode(r))
    ser.write(b'^')
    ser.write(str.encode(g))
    ser.write(b'^')
    ser.write(str.encode(b))
    ser.write(b'^')

class Handler:
    def onDeleteWindow(self, *args):
        Gtk.main_quit(*args)

    def toggle_power(self, button):
        print("Toggled Power")
    def set_port(self, button):
        get = builder.get_object('port_input').get_text()
        if not get:
            print("Input a port")
        else:
            print("Setting port to: ")
            ser = serial.Serial(get, 9600)

    def set_delay(self, button):
        print("Setting delay to: ")

    def set_color(self, button):
        print("Setting color to: ")
        red = builder.get_object('r_value').get_text()
        green = builder.get_object('g_value').get_text()
        blue = builder.get_object('b_value').get_text()
        send_color(red, green, blue)

    def set_brightness(self, button):
        brightness = builder.get_object('brightness_input').get_text()
        print("Setting brightness to: ", brightness)
        ser.write(b'b')
        ser.write(str.encode(brightness))
        ser.write(b'^')

    def set_rotation(self, button):
        print("Setting rotation to: ")
    def on_green(self, button):
        ser.write(b'2')
    def on_blue(self, button):
        ser.write(b'1')
    def on_red(self, button):
        ser.write(b'0')
    def onReset(self, button):
        print("Setting rotation to: ")
        #       print(builder.get_object('rotation_input').get_text())
        #       controller.set_rotation(builder.get_object('rotation_input').get_text())

builder.connect_signals(Handler())
win.show_all()
Gtk.main()
