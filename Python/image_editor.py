from tkinter import *
from PIL import ImageTk, Image
from tkinter import filedialog
import os
from tkinter import ttk
import ctypes

label_image = None

function = ctypes.CDLL('../C/imgedit.so').photo
function.argtypes = [ctypes.c_char_p, ctypes.c_int, ctypes.c_char_p]

root = Tk()
root.attributes("-zoomed", True)
style = ttk.Style(root)

style.theme_use('clam')

screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()

root.title('Image Editor')
root.geometry("1200x800")

def open_image():
    global curr_img, label_image
    root.filename = filedialog.askopenfilename(initialdir="", title="Select the image", filetypes=(("PPM", "*.ppm"), ("PNG", "*.png"), ("JPG", "*.jpg")))
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

    curr_img.save("working_img.ppm")
    curr_img = Image.open("working_img.ppm")
    curr_img = ImageTk.PhotoImage(curr_img)
    label_image = Label(image=curr_img, bd=10)
    label_image.grid(row=0, column=1, rowspan=100)


def process_image():
    deg_rot = rotation_var.get()
    filt = filter.get()
    print(deg_rot)
    print(path)

    path_enc = path.encode('utf-8')
    angle = int(deg_rot)
    filter_name = filt.encode('utf-8')  # Convert filter name to bytes

    label_image.destroy()
    # Call the function
    function(path_enc, angle, filter_name)
    print(path)
    return


ttk.Separator(root, orient=VERTICAL).grid(column=1, row=0, rowspan=100, sticky='sn')


load_button = Button(root, text="Select image", command=open_image, padx=10, pady=10, bd=7, font=('Helvetica', 14)).grid(row=0, column=0, padx=40, pady=40)


filter = StringVar()
filter.set("None")
filters_label = Label(text="Filters", padx=5, pady=15, height=3, anchor=S, font=('Helvetica', 14)).grid(row=1, column=0)
drop_menu_filters = OptionMenu(root, filter, "EDGE", "BLUR", "SHARPEN", "GAUSSIAN_BLUR")
drop_menu_filters.config(width = 10, height = 1, pady = 6,font=('Helvetica', 14))
menu = drop_menu_filters.nametowidget(drop_menu_filters.menuname)
menu.config(font=('Helvetica', 12))
drop_menu_filters.grid(row=2, column=0)

Label(height=6).grid(row=3, column=0)

filters_label = Label(text="Rotate", padx=5, pady=15, height=3, anchor=S, font=('Helvetica', 15)).grid(row=4, column=0)
rotation_var = StringVar()
rotation_var.set(0)

angle_0_radio = Radiobutton(root, text="No rotation", variable=rotation_var, value=0, font=('Helvetica', 13), padx=3)
angle_0_radio.grid(row=5, column=0, padx=6, pady=4)

angle_90_radio = Radiobutton(root, text="Rotate 90°", variable=rotation_var, value=90, font=('Helvetica', 13), padx=3)
angle_90_radio.grid(row=6, column=0, padx=6, pady=4)

angle_180_radio = Radiobutton(root, text="Rotate 180°", variable=rotation_var, value=180, font=('Helvetica', 13), padx=3)
angle_180_radio.grid(row=7, column=0, padx=6, pady=4)

angle_270_radio = Radiobutton(root, text="Rotate 270°", variable=rotation_var, value=270, font=('Helvetica', 13), padx=3)
angle_270_radio.grid(row=8, column=0, padx=6, pady=4)



Label(height=4).grid(row=9, column=0)

apply_button = Button(root, text="Apply selection", command=process_image, padx=30, pady=8, bd=2, font=('Helvetica', 14)).grid(row=10, column=0, padx=10, pady=10, sticky="s")

root.mainloop()

if os.path.exists("working_img.ppm"):
    os.remove("working_img.ppm")

print("Thanks for using this program :)")