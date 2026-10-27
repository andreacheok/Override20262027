/* Unit conversions: degrees to radians and back, inches to wheel ticks or degrees, and ticks to inches. You’ll use these constantly in odometry.
Angle utilities: wrapping an angle to a fixed range (like -180 to 180), and finding the shortest signed difference between two headings. Turning PID breaks without this.
Clamping and limiting: keeping a value within min/max bounds, which you’ll use for motor power limits.
Sign and absolute value helpers, plus a simple “is this within tolerance of that” check.
Basic geometry: distance between two points and angle from one point to another, for driving to coordinates later.
Constants: pi and anything else you’d otherwise retype.
*/
