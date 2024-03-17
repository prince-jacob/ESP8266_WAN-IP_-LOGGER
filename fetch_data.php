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

// Fetch IP addresses from the database
$sql = "SELECT ip_address, timestamp FROM ip_addresses ORDER BY timestamp DESC LIMIT 10";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // Output data of each row
    while ($row = $result->fetch_assoc()) {
        echo "IP Address: " . $row["ip_address"] . " - Timestamp: " . $row["timestamp"] . "<br>";
    }
} else {
    echo "No IP addresses found.";
}

$conn->close();
?>
