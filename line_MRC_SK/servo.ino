void servo(int ch, int degree) {
  if (ch == 1) {
    if (degree == -1) myservo[0].detach();
    else {
      if (!myservo[0].attached()) myservo[0].attach(9);
      myservo[0].write(degree);
    }
  }
  else if (ch == 2) {
    if (degree == -1) myservo[1].detach();
    else {
      if (!myservo[1].attached()) myservo[1].attach(10);
      myservo[1].write(degree);
    }
  }
  else if (ch == 3) {
    if (degree == -1) myservo[2].detach();
    else {
      if (!myservo[2].attached()) myservo[2].attach(11);
      myservo[2].write(degree);
    }
  }
}