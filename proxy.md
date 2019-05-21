# Instructions

```bash
# Disable static ip, comment out lines using '#' at start of lines
sudo nano /etc/dhcpcd.conf

# Add persistents proxy env vars
sudo nano /etc/environment

# Add this lines to the file (should be empty)
export http_proxy="http://172.21.1.211:3128"
export https_proxy="https://172.21.1.211:3128"
export no_proxy="localhost, 127.0.0.1"

# Extend proxy env vars to sudoers
sudo visudo

# Add this line after the other 'Defaults' lines (in the middle of the file)
Defaults    env_keep+="http_proxy https_proxy no_proxy"

# Reboot the device
sudo reboot

# Test if internet is working
sudo apt-get update
```
