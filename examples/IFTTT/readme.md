# An Internet of Buttons
One of the most versatile uses of the Frame.IoT is leveraging the perfectly-positioned pushbutton (on digital pin 16) to trigger action in the world through platforms like IFTTT, Zapier, or your own native integrations with home automation platforms like Google Home, Apple Homekit, and Alexa.

In this example, we're saving a lot of the coding headache by simply sending a `POST` request to an existing endpoint in IFTTT. IFTTT handles the rest and triggers a push notification the registered device with the IFTTT app installed.

### Steps to recreate:
1. Fork/download the above `IFTTT.ino` sketch. Make sure you have all the libraries that are included or else the sketch won't compile
2. Change the `ssid` and `password` variables to match your network. (You can build upon this sketch to add your own networking handling and captive portals.)
3. Download the IFTTT mobile app for iOS/Android and create/login to a free account.
4. Create a new Applet and configure the trigger to be a Webhook. Note your `Event Name` and your `key`.
5. Going back to the sketch, replace the following line with your endpoint: `http.begin("https://maker.ifttt.com/trigger/{your_action}/with/key/{your_key}");`. It's safe to compile and upload this sketch to your Frame.IoT now.
6. In IFTTT, add an action step. We used the built-in notification system to trigger an alert but the possibilities are endless. You could even pass sensor data into the HTTP POST request and leverage the data on the action side.

Happy making!
