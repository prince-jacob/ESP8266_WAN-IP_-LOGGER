# Arduino-IP-Tracker

This project involves an Arduino sketch for tracking public IP addresses and PHP scripts for saving and fetching IP data from a MySQL database. It's designed to work with an ESP8266 board (e.g., ESP-01, NodeMCU) connected to a WiFi network.

## Features

- Retrieves public IP address using ipify API
- Saves IP addresses to a MySQL database via PHP script
- Fetches and displays saved IP addresses in a modern UI
- Error handling for database connection and HTTP requests

## Getting Started

### Prerequisites

- Arduino IDE
- ESP8266 board and USB cable
- MySQL database server
- Web server with PHP support (e.g., Apache, Nginx)

### Installation

1. Clone or download this repository to your local machine.
2. Upload the Arduino sketch (`Arduino_IP_Tracker.ino`) to your ESP8266 board using the Arduino IDE.
3. Set up a MySQL database and execute the provided SQL query (`database_query.sql`) to create the necessary table.
4. Place the PHP scripts (`save_ip.php`, `fetch_data.php`, and `display_ips.php`) on your web server with PHP support.

## Usage

1. Connect the ESP8266 board to a power source and ensure it's connected to the WiFi network.
2. The Arduino code will periodically fetch the public IP address and send it to the `save_ip.php` script on your server.
3. Access the `display_ips.php` script in your web browser to view the saved IP addresses in a modern UI.

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests with improvements or bug fixes.




