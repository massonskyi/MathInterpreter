import os

def rename_files(directory):
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith('.txt'):
                old_file = os.path.join(root, file)
                new_file = os.path.join(root, file[:-4] + '.h')
                os.rename(old_file, new_file)
                print(f'Renamed: {old_file} to {new_file}')

# Specify the directory where the script should start renaming files
directory_to_search = os.path.join(os.getcwd(), "include/") # Replace with your desired directory path

# Call the function to rename files
rename_files(directory_to_search)
