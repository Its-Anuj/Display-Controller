import serial
import time
import tkinter as tk

# The Port and the Serial Init Num
# Port = input("Enter Port: ")
# Buad = int(input("Enter Baud: "))

# arduino = serial.Serial(Port, Buad)
arduino = serial.Serial("COM4", 9600)

# Not Understood but wait for arduino to reset
time.sleep(2)


def on_button_click():
    parsestring = f"{entry.get()}\n"

    Valid = False

    if(int(parsestring) < 10000 and (float(parsestring) - int(parsestring) == 0)):
        Valid = True

    if(Valid):
        arduino.write(parsestring.encode())

    print("Sleeping for 2 Seconds!!...")
    time.sleep(2)
    print("Online!!")

root = tk.Tk()
root.title("Display Controller")

# Text input (Entry)
entry = tk.Entry(root, width=10)
entry.pack(pady=10)
# Create a button and bind it to the function
button = tk.Button(root, text="Submit", command=on_button_click)
button.pack(padx=20, pady=20)

print("Update Check")

root.mainloop()

arduino.close()

