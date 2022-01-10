import tkinter as tk
from tkinter.colorchooser import askcolor


root = tk.Tk()
root.title('Tkinter Color Chooser')
root.geometry('300x150')
canvas = tk.Canvas(
    root,
    height=20,
    width=20,
    bg="#fff"
    )
canvas.pack()

def change_color():
    colors = askcolor(title="Tkinter Color Chooser")
    root.configure(bg=colors[1])


tk.Button(
    root,
    text='Select a Color',
    command=change_color).pack(expand=True)

w = tk.Entry(root,width=10)
w.place(x=50, y=50)
R = w.get()
canvas.create_rectangle(
    0, 0, 20, 20,
    outline="#fb0",
    fill="#fb0")
root.mainloop()