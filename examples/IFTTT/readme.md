# An Internet of Buttons
One of the most versatile uses of the Frame.IoT is leveraging the perfectly-positioned pushbutton (on digital pin 16) to trigger action in the world through platforms like IFTTT, Zapier, or your own native integrations with home automation platforms like Google Home, Apple Homekit, and Alexa.

In this example, we're saving a lot of the coding headache by simply sending a `POST` request to an existing endpoint in IFTTT. IFTTT handles the rest and triggers a push notification the registered device with the IFTTT app installed.
