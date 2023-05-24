from tkinter import *
from PIL import ImageTk, Image
from tkinter import filedialog
import os
from tkinter import ttk
import ctypes
import customtkinter as ctk

label_image = None
mode = 1

function = ctypes.CDLL('../C/imgedit.so').photo
function.argtypes = [ctypes.c_char_p, ctypes.c_int, ctypes.c_char_p, ctypes.c_char_p]

root = ctk.CTk()
root.attributes("-zoomed", True)

ctk.set_default_color_theme("green")

if mode == 1:
    ctk.set_appearance_mode("dark")
else:
    ctk.set_appearance_mode("light")

font_large = ("Roboto-Regular", 28)
font_medium = ("Roboto-Regular", 22)
font_small = ("Roboto-Regular", 18)

screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()

root.title('Image Editor')
root.geometry("1200x800")


def switch_event():
    global mode
    mode = switch_var.get()
    if mode == 1:
        ctk.set_appearance_mode("dark")
    else:
        ctk.set_appearance_mode("light")


def open_image():
    global curr_img, label_image
    root.filename = ctk.filedialog.askopenfilename(initialdir="../Images", title="Select the image", filetypes=(("PPM", "*.ppm"), ("PNG", "*.png"), ("JPG", "*.jpg")))
    global path
    path = root.filename
    if root.filename:
        print("Opening " + os.path.basename(root.filename))
    else:
        return
    curr_img = Image.open(root.filename)

    width, height = curr_img.size
    new_width, new_height = width, height
    if width > screen_width * 0.88 or height > screen_height * 0.92:
        ratio = min(screen_width * 0.88 / width, screen_height * 0.92 / height)
        new_width = int(width * ratio)
        new_height = int(height * ratio)
        curr_img = curr_img.resize((new_width, new_height), Image.ANTIALIAS)

    
    curr_img.save("../Images/working_img.ppm")
    curr_img = ctk.CTkImage(dark_image=Image.open("../Images/working_img.ppm"), size=(new_width, new_height))
    # curr_img = ImageTk.PhotoImage(curr_img)
    label_image = ctk.CTkLabel(root, image=curr_img, text="")
    label_image.grid(row=0, column=1, rowspan=100)
    
def save_image():
    save_path = ctk.filedialog.asksaveasfilename(defaultextension=".jpg")
    if save_path:
        curr_img.save(save_path)
        print("Image saved successfully.")

    # f = ctk.filedialog.asksaveasfile(mode='w', defaultextension=".jpg")
    # if f is None:
    #     return
    # text2save = str("idk")
    # f.write(text2save)
    # f.close()



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
    new_width, new_height = width, height
    if width > screen_width * 0.88 or height > screen_height * 0.92:
        ratio = min(screen_width * 0.88 / width, screen_height * 0.92 / height)
        new_width = int(width * ratio)
        new_height = int(height * ratio)
        curr_img = curr_img.resize((new_width, new_height), Image.ANTIALIAS)

    curr_img.save("../Images/working_img.ppm")
    curr_img = ctk.CTkImage(dark_image=Image.open("../Images/working_img.ppm"), size=(new_height, new_height))
    label_image = ctk.CTkLabel(root, image=curr_img, text="")
    label_image.grid(row=0, column=1, rowspan=100)
    return

frame = ctk.CTkFrame(master=root, width=900, height=900).bind(sequence=None)

load_button = ctk.CTkButton(root, text="Select image", command=open_image, font=font_large, height=55, width=225).grid(row=0, column=0, padx=60, pady=40)

filter = StringVar()
filter.set("None")
filters_label = ctk.CTkLabel(root, text="Filters", padx=5, pady=15, height=3, anchor=S, font=font_large).grid(row=1, column=0)
drop_menu_filters = ctk.CTkOptionMenu(root, values=["None", "EDGE", "BLUR", "SHARPEN", "GAUSSIAN_BLUR"], variable=filter, dropdown_font=font_medium, width=50, height=40)
drop_menu_filters.configure(width = 100, height = 40, font=font_medium)
drop_menu_filters.grid(row=2, column=0)

ctk.CTkLabel(root, text="", height=70).grid(row=3, column=0)

filters_label = ctk.CTkLabel(root, text="Rotate", padx=5, pady=15, height=3, anchor=S, font=font_large, corner_radius=15).grid(row=4, column=0)
rotation_var = ctk.IntVar(value = 0)

angle_0_radio = ctk.CTkRadioButton(root, text="No rotation", variable=rotation_var, value=0, font=font_small, height=35)
angle_0_radio.grid(row=5, column=0, padx=6, pady=4)

angle_90_radio = ctk.CTkRadioButton(root, text="Rotate 90°", variable=rotation_var, value=90, font=font_small, height=35)
angle_90_radio.grid(row=6, column=0, padx=6, pady=4)

angle_180_radio = ctk.CTkRadioButton(root, text="Rotate 180°", variable=rotation_var, value=180, font=font_small, height=35)
angle_180_radio.grid(row=7, column=0, padx=6, pady=4)

angle_270_radio = ctk.CTkRadioButton(root, text="Rotate 270°", variable=rotation_var, value=270, font=font_small, height=35)
angle_270_radio.grid(row=8, column=0, padx=6, pady=4)


ctk.CTkLabel(root, text="", height=60, font=font_large).grid(row=9, column=0)

apply_button = ctk.CTkButton(root, text="Apply selection", command=process_image, font=font_large, height=55, width=240).grid(row=10, column=0, padx=10, pady=10, sticky="s")

save_button = ctk.CTkButton(root, text="Save Image", command=save_image, font=font_large, height=55, width=225)
save_button.grid(row=11, column=0, padx=60, pady=40)

    

switch_var = ctk.IntVar(value = 1)
switch = ctk.CTkSwitch(root, text="", command=switch_event, variable=switch_var, onvalue=1, offvalue=0, switch_height=30, switch_width=65).grid(row=12, column=0, padx=40, pady=25)


root.mainloop()

# if os.path.exists("working_img.ppm"):
#     os.remove("working_img.ppm")

print("Thanks for using this program :)")