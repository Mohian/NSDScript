import os
import requests

def download_file(url, filename):
    downloads_path = os.path.join(os.path.expanduser('~'), 'Downloads')
    filepath = os.path.join(downloads_path, filename)
    
    response = requests.get(url, stream=True)
    if response.status_code == 200:
        with open(filepath, 'wb') as file:
            for chunk in response.iter_content(1024):
                file.write(chunk)
        print(f"{filename} downloaded successfully to {downloads_path}.")
    else:
        print(f"Failed to download {filename}.")

def main():
    file_path = "software_list.txt"  # The text file containing software links
    
    if not os.path.exists(file_path):
        print("Error: software_list.txt not found!")
        return
    
    with open(file_path, 'r') as file:
        for line in file:
            line = line.strip()
            if "=" in line:
                name, url = line.split("=", 1)
                choice = input(f"Download {name}? (y/n): ").strip().lower()
                if choice == 'y':
                    filename = url.split("/")[-1]  # Extracting filename from URL
                    download_file(url, filename)
                else:
                    print(f"Skipping {name}.")
    
    print("All tasks completed.")

if __name__ == "__main__":
    main()
