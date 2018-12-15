# Notes: Missing handling exceptions on files - user may delete files locally and program will crash
#        Missing better GUI - no window resizement while scrolling through images
#        Missing downloading from server to a specific directory and not to current working one
#        Missing checking whether files from server are actually images
#        Deleting files at end of process so no leftovers remain after user handles data - might be problamatic if user wants to change choices
#        To fix above problem: add a submit button after dictionary size is large as original file list (no deletion occurs) so user can decide to upload

import boto3
from botocore import UNSIGNED
from botocore.config import Config
import os
import tkinter as tk
from PIL import Image, ImageTk
import pickle

def download_images():
    file_list = []
    # Choose the bucket as provided by input
    image_bucket = s3.Bucket(bucket_name)
    # Go through all files/folders in bucket
    for object in image_bucket.objects.all():
        # Separate folder and file names
        path, filename = os.path.split(object.key)
        # Download the file as 'filename'
        image_bucket.download_file(object.key, filename)
        file_list.append(filename)
    return file_list

def next_image(direction):
    global current_index
    # Advance to new index on list: direction = 1 forward, -1 for backwards
    current_index = (current_index + direction) % len(file_list)
    img = ImageTk.PhotoImage(Image.open(file_list[current_index]))
    image_panel.configure(image=img)
    # Probaly delete:
    image_panel.image = img

def add_to_dict(value):
    global count
    # Add user choice to dictionary
    user_choices[file_list[current_index]] = value
    # Delete valued image from list
    os.remove(file_list[current_index])
    del file_list[current_index]
    count -= 1
    # If we passed through all images, upload and finish
    if (count == 0):
        upload_file()
    # If there are images left, move to next one
    else:
        next_image(0)
        
def upload_file():
    filename = "user_choices.bin"
    # Open file to write as binary
    bin_file = open(filename, 'wb')
    # Pickle the file
    pickle.dump(user_choices, bin_file)
    # Use filename both as the file name and key, since file in current working directory
    bin_file.close()
    s3.Bucket(bucket_name).upload_file(filename, filename)
    # Optional deletion of binary file, not in use so we can check the file works
    #os.remove(filename)
    # Finished going through pictures, exit program
    window.destroy()
    raise SystemExit
    

# Initiate s3 resource
bucket_name = "nanit-for-exercise"
s3 = boto3.resource('s3', config=Config(signature_version=UNSIGNED))
# Download all images from bucket
file_list = download_images()
# Dictionary to keep user choices as "filename:value"
user_choices = {}
# Globals to know the current image index and amount of images processed
current_index = 0
count = len(file_list)
# Creating GUI
window = tk.Tk()
window.configure(background = "light blue")
image_panel = tk.Label(window)
# Show first image
next_image(0)
# Configure forward and backward buttons, use lambda to pass arguments to function
forward_button = tk.Button(window, text = "Forward", bg = "light green", command = lambda: next_image(1))
backward_button = tk.Button(window, text = "Backward", bg = "light green", command = lambda: next_image(-1))
# Configure bottom buttons
horses_button = tk.Button(window, text = "Horses", bg = "#add0ff", command = lambda: add_to_dict("horses"))
birds_button = tk.Button(window, text = "Birds", bg = "#add0ff", command = lambda: add_to_dict("birds"))
flowers_button = tk.Button(window, text = "Flowers", bg = "#add0ff", command = lambda: add_to_dict("flowers"))
# Placing objects in grid   
image_panel.grid(row = 0, column = 1, padx = 50, pady = 100)
forward_button.grid(row = 0, column = 2, padx = 50, pady = 100)
backward_button.grid(row = 0, column = 0, padx = 50, pady = 100)
horses_button.grid(row = 1, column = 0, padx = 25, pady = 50)
birds_button.grid(row = 1, column = 1, padx = 25, pady = 50)
flowers_button.grid(row = 1, column = 2, padx = 25, pady = 50)
window.mainloop()
