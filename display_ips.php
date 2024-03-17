<?php
// Database credentials
$servername = "localhost";
$username = "your_username";
$password = "your_password";
$database = "your_database";

// Create connection
$conn = new mysqli($servername, $username, $password, $database);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Fetch latest 2 IP addresses from the database
$sql = "SELECT ip_address, timestamp FROM ip_addresses ORDER BY timestamp DESC LIMIT 2";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // Start HTML output
    echo '<!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta http-equiv="refresh" content="5"> <!-- Auto-refresh every 5 seconds -->
        <title>IP Addresses</title>
        <style>
            body {
                font-family: Arial, sans-serif;
                background-color: #f4f4f4;
                padding: 20px;
            }
            .container {
                max-width: 800px;
                margin: 0 auto;
            }
            h1 {
                color: #333;
                text-align: center;
            }
            .ip-card {
                background-color: #fff;
                border-radius: 8px;
                padding: 20px;
                margin-bottom: 15px;
                box-shadow: 0px 2px 5px rgba(0, 0, 0, 0.1);
            }
            .ip-card p {
                margin: 0;
            }
            .ip-address {
                font-size: 24px;
                color: #007bff;
            }
            .timestamp {
                color: #666;
            }
        </style>
    </head>
    <body>
        <div class="container">
            <h1>IP Addresses</h1>';

    // Output data of each row
    while ($row = $result->fetch_assoc()) {
        echo '<div class="ip-card">
            <p class="ip-address">IP Address: ' . $row["ip_address"] . '</p>
            <p class="timestamp">Timestamp: ' . $row["timestamp"] . '</p>
        </div>';
    }

    // End HTML output
    echo '</div></body></html>';
} else {
    echo "No IP addresses found.";
}

$conn->close();
?>
