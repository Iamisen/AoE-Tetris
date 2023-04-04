# AoE-Tetris

Based on those resources, the arduino Trinket (or whatsoever) would be the master and the LED matrix’s chip is the slave

We should read analog data entered by the user through the buttons process that and then send commands to the screen

I think we'll need three sketches
	One for the menu
	One for the game loop itself
	One for the Matrix

If we wanna separate everything we can also code the I2C communication on a different sketch
