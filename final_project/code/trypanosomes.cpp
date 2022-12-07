#include "functions.cpp"
#include <cmath>
#include "cpgplot.h"
#include <iostream>

int main()
{
  //taking interval input from terminal
  int n;
  std::cout << "Enter number of steps: " << "\n";
  std::cin >> n;
  
  //setting float arrays for plotting
  float tp[n+1], yp[n+1], xp[n+1], xpyp[n+1], cp[n+1];

  // Open a plot window
  if (!cpgopen("/XWINDOW")) return 1;

  // Set-up plot axes
  cpgenv(48.,320., 5., 10., 0, 1);
  // Label axes
  cpglab("Time (h)", "Cells/mL", "");
 
  //Setting up the runge-kutta method
  double vx1, vy1, vc1, vx2, vy2, vc2, vx3, vy3, vc3, vx4, vy4, vc4, dt, x, y, c, t, t_end, r, r2, f0, m2, m;

  //setting parameters
  t_end = 320.00;
  dt = t_end/n;
  y = 1e-10; //change this
  t = 0.00;
  x = 3910.00; //X0 value from paper
  r = 0.11;
  f0 = 1.2e-9;
  m = 0.012;
  m2 = 0.02; //mortality rate of malaria causing cells
  c = 3.91e9; //population of malaria causing cells
  r2 = 0.20;  //rate of division of malaria causing cells

  //Initializing arrays
  tp[0] = t; 
  yp[0] = log10(y);
  xp[0] = log10(x);
  xpyp[0] = log10(x + y);
  cp[0] = log10(c);

  // Compute the function at the points
  for (int i=1;i<=n;i++) {

    vx1 = dt * (dxdt(x,y,r,f0));
    vy1 = dt * (dydt(x,y,f0,m));
    vc1 = dt * (dcdt(x,y,c,f0,m,m2,r2));

    vx2 = dt * (dxdt((x + 0.5 * vx1), (y + 0.5 * vy1), r, f0));
    vy2 = dt * (dydt((x + 0.5 * vx1), (y + 0.5 * vy1), f0, m));
    vc2 = dt * (dcdt((x + 0.5 * vx1), (y + 0.5 * vy1), (c + 0.5 * vc1), f0, m, m2, r2));

    vx3 = dt * (dxdt((x + 0.5 * vx2), (y + 0.5 * vy2), r, f0));
    vy3 = dt * (dydt((x + 0.5 * vx2), (y + 0.5 * vy2), f0, m));
    vc3 = dt * (dcdt((x + 0.5 * vx2), (y + 0.5 * vy2), (c + 0.5 * vc2), f0, m, m2, r2));

    vx4 = dt * (dxdt((x + vx3), (y + vy3), r, f0));
    vy4 = dt * (dydt((x + vx3), (y + vy3), f0, m));
    vc4 = dt * (dcdt((x + vx3), (y + vy3), (c + vc3), f0, m, m2, r2));

    t = t + dt;

    x = x + (vx1 + (2.00 * vx2) + (2.00 * vx3) + vx4 )/6;
    y = y + (vy1 + (2.00 * vy2) + (2.00 * vy3) + vy4 )/6;
    c = c + (vc1 + (2.00 * vc2) + (2.00 * vc3) + vc4 )/6;

    std::cout << x << "\n";

    tp[i] = t;
    yp[i] = log10(y);
    xp[i] = log10(x);
    xpyp[i] = log10(x + y);

    if (c <= 0) {
        cp[i] = 0.00;
    } else {
        cp[i] = log10(c);
    }
  }

  std::cout << "Number of steps: " << n << "\n";
  std::cout << "timestep (deltat): " << dt << "\n";
  std::cout << "final y(t=10): " << y << "\n";
  //std::cout << "final error at t=10: " << exact_y - y << "\n";
  //std::cout << "final error at t=10 divided by deltat: " << (exact_y - y)/pow(dt,4) << "\n";

  // Plot the curve 
  // This line is
  cpgsci(4);
  cpgline(n+1,tp,yp);
  // Plot the next curve
  // This line is
  cpgsci(2);
  cpgline(n+1,tp,xp);
  // Plot the next curve
  // This line is
  cpgsci(3);
  cpgline(n+1, tp, xpyp);
  //Plot the next curve
  cpgsci(8);
  cpgline(n+1, tp, cp);
  // Pause and then close plot window
  cpgclos();
}
