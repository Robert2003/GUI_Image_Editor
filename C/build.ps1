# Set the path to the directory containing the .c files
$sourceDirectory = "C:\Users\rober\OneDrive\Desktop\Proiect_PCLP3\GUI_Image_Editor"

# Set the path to the directory where you want to store the object files
$objectDirectory = "C:\Users\rober\OneDrive\Desktop\Proiect_PCLP3\GUI_Image_Editor"

# Get the list of .c files in the source directory
$cFiles = Get-ChildItem -Path $sourceDirectory -Filter "*.c"

# Loop through each .c file and compile it to an object file
foreach ($cFile in $cFiles) {
    # Build the output object file path
    $objectFile = Join-Path -Path $objectDirectory -ChildPath ($cFile.BaseName + ".o")
    
    # Execute the compilation command
    & gcc -c $cFile.FullName -o $objectFile
}
