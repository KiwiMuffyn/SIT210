import RPi.GPIO as GPIO
import tkinter as tk
LED_pin = 4
GPIO.setmode(GPIO.BCM)
GPIO.setup(LED_pin, GPIO.OUT)

def led_on():
    GPIO.output(LED_pin, GPIO.HIGH)

def led_off():
    GPIO.output(LED_pin, GPIO.LOW)

def on_closing():
    GPIO.output(LED_pin,GPIO.LOW)
    GPIO.cleanup()
    window.destroy()
    
window = tk.Tk()
window.title("LED Controller")
window.geometry("300x150")

on_button = tk.Button(window, text = "Turn LED on ",command = led_on, bg = "green", fg = "white", width = 20)
on_button.pack(pady = 10)

off_button = tk.Button(window, text = "Turn LED off", command = led_off, bg = "red", fg = "white", width = 20)
off_button.pack(pady = 10)

window.protocol("WM_DELETE_WINDOW", on_closing)
window.mainloop()