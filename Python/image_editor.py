from tkinter import *
from PIL import ImageTk, Image
from tkinter import filedialog
import os
from tkinter import ttk
import ctypes
import customtkinter as ctk

label_image = None

function = ctypes.CDLL('../C/imgedit.so').photo
function.argtypes = [ctypes.c_char_p, ctypes.c_int, ctypes.c_char_p, ctypes.c_char_p]

root = ctk.CTk()
root.attributes("-zoomed", True)
# style = ttk.Style(root)

# style.theme_use('clam') 

font_large = ("Roboto-Regular", 28)
font_medium = ("Roboto-Regular", 22)
font_small = ("Roboto-Regular", 18)

screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()

root.title('Image Editor')
root.geometry("1200x800")

def open_image():
    global curr_img, label_image
    root.filename = filedialog.askopenfilename(initialdir="../Images", title="Select the image", filetypes=(("PPM", "*.ppm"), ("PNG", "*.png"), ("JPG", "*.jpg")))
    global path
    path = root.filename
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

    
    curr_img.save("../Images/working_img.ppm")
    curr_img = ctk.CTkImage(dark_image=Image.open("../Images/working_img.ppm"), size=(width, height))
    # curr_img = ImageTk.PhotoImage(curr_img)
    label_image = ctk.CTkLabel(root, image=curr_img, text="")
    label_image.grid(row=0, column=1, rowspan=100)
    

def process_image():
    global label_image, curr_img
    deg_rot = rotation_var.get()
    filt = filter.get()
    save = "../Images/working_img.ppm"
    save_enc = save.encode('utf-8')
    path_enc = path.encode('utf-8')
    angle = int(deg_rot)
    filter_name = filt.encode('utf-8')

    function(path_enc, angle, filter_name, save_enc)
    label_image.destroy()

    curr_img = Image.open("../Images/working_img.ppm")
    width, height = curr_img.size
    if width > screen_width * 0.88 or height > screen_height * 0.92:
        ratio = min(screen_width * 0.88 / width, screen_height * 0.92 / height)
        new_width = int(width * ratio)
        new_height = int(height * ratio)
        curr_img = curr_img.resize((new_width, new_height), Image.ANTIALIAS)

    curr_img.save("../Images/working_img.ppm")
    curr_img = ctk.CTkImage(dark_image=Image.open("../Images/working_img.ppm"), size=(width, height))
    label_image = ctk.CTkLabel(root, image=curr_img, text="")
    label_image.grid(row=0, column=1, rowspan=100)
    return


load_button = ctk.CTkButton(root, text="Select image", command=open_image, font=font_large).grid(row=0, column=0, padx=60, pady=40)

filter = StringVar()
filter.set("None")
filters_label = ctk.CTkLabel(root, text="Filters", padx=5, pady=15, height=3, anchor=S, font=font_large).grid(row=1, column=0)
drop_menu_filters = ctk.CTkOptionMenu(root, values=["None", "EDGE", "BLUR", "SHARPEN", "GAUSSIAN_BLUR"], variable=filter, dropdown_font=font_medium, anchor="center", height=40)
drop_menu_filters.configure(width = 15, height = 1,font=font_medium)
drop_menu_filters.grid(row=2, column=0)

ctk.CTkLabel(root, text="", height=70).grid(row=3, column=0)

filters_label = ctk.CTkLabel(root, text="Rotate", padx=5, pady=15, height=3, anchor=S, font=font_large).grid(row=4, column=0)
rotation_var = ctk.StringVar()
rotation_var.set(0)

angle_0_radio = ctk.CTkRadioButton(root, text="No rotation", variable=rotation_var, value=0, font=font_small, height=35)
angle_0_radio.grid(row=5, column=0, padx=6, pady=4)

angle_90_radio = ctk.CTkRadioButton(root, text="Rotate 90°", variable=rotation_var, value=90, font=font_small, height=35)
angle_90_radio.grid(row=6, column=0, padx=6, pady=4)

angle_180_radio = ctk.CTkRadioButton(root, text="Rotate 180°", variable=rotation_var, value=180, font=font_small, height=35)
angle_180_radio.grid(row=7, column=0, padx=6, pady=4)

angle_270_radio = ctk.CTkRadioButton(root, text="Rotate 270°", variable=rotation_var, value=270, font=font_small, height=35)
angle_270_radio.grid(row=8, column=0, padx=6, pady=4)


ctk.CTkLabel(root, text="", height=60, font=font_large).grid(row=9, column=0)

apply_button = ctk.CTkButton(root, text="Apply selection", command=process_image, font=font_large).grid(row=10, column=0, padx=10, pady=10, sticky="s")

root.mainloop()

# if os.path.exists("working_img.ppm"):
#     os.remove("working_img.ppm")

print("Thanks for using this program :)")