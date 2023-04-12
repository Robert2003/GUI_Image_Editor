from tkinter import *
from PIL import ImageTk, Image
from tkinter import filedialog
import os
import ctypes

root = Tk()

screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()

root.title('Image Editor')
# root.geometry(str(screen_width) + "x" + str(screen_height));
root.geometry("1200x800")
# root.configure(bg="#669990")

def open_image():
    global curr_img
    root.filename = filedialog.askopenfilename(initialdir="", title="Select the image", filetypes=(("PPM", "*.ppm"), ("PNG", "*.png"), ("JPG", "*.jpg")))
    if root.filename:
        print("Opening " + os.path.basename(root.filename))
    else:
        return
    curr_img = Image.open(root.filename)

    width, height = curr_img.size
    if width > screen_width * 0.88 or height > screen_height * 0.92:
        ratio = min(screen_width * 0.88 / width, screen_height * 0.92 / height)
        new_width = int(width * ratio)
        new_height = int(height * ratio)
        curr_img = curr_img.resize((new_width, new_height), Image.ANTIALIAS)

    curr_img.save("working_img.ppm")
    curr_img = Image.open("working_img.ppm")
    curr_img = ImageTk.PhotoImage(curr_img)
    label_image = Label(image=curr_img, bd=10).grid(row=0, column=1, rowspan=100)


def process_image():
    return



filter = StringVar()
filter.set("None")
filters_label = Label(text="Filters", pady=5, padx=5, height=3, anchor=S, font=14).grid(row=1, column=0)
drop_menu_filters = OptionMenu(root, filter, "None", "Blur", "Sharpen", "Gaussian blur").grid(row=2, column=0)

Label(height=2).grid(row=4, column=0)

rotation_var = StringVar()
rotation_var.set(0)

angle_0_radio = Radiobutton(root, text="No rotation", variable=rotation_var, value=0, font=14, padx=3)
angle_0_radio.grid(row=5, column=0, padx=6, pady=4)

angle_90_radio = Radiobutton(root, text="Rotate 90°", variable=rotation_var, value=90, font=14, padx=3)
angle_90_radio.grid(row=6, column=0, padx=6, pady=4)

angle_180_radio = Radiobutton(root, text="Rotate 180°", variable=rotation_var, value=180, font=14, padx=3)
angle_180_radio.grid(row=7, column=0, padx=6, pady=4)

angle_270_radio = Radiobutton(root, text="Rotate 270°", variable=rotation_var, value=270, font=14, padx=3)
angle_270_radio.grid(row=8, column=0, padx=6, pady=4)


load_button = Button(root, text="Select image", command=open_image, padx=8, pady=8, bd=5, font=14).grid(row=0, column=0, padx=25, pady=20)


Label(height=2).grid(row=9, column=0)

apply_button = Button(root, text="Apply selection", command=open_image, padx=30, pady=8, bd=2, font=14).grid(row=10, column=0, padx=10, pady=10, sticky="s")

root.mainloop()

if os.path.exists("working_img.ppm"):
    os.remove("working_img.ppm")

print("Thanks for using this program:)")