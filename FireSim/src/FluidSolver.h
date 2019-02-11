#ifndef FluidSolver_h
#define FluidSolver_h

#include <stdio.h>
#include <vector>
#include <iostream>

using grid = std::vector<double>;
class FluidSolver{
public:
    FluidSolver(int n = 64, double diff = 0.0, double visc = 0.0, double dt=0.1);
    ~FluidSolver();

    void reset();
    
    void timeStep();
    
    void addVelocity(int i, int j, double u, double v);
    void addDensity(int i, int j);
    
    double getDensityAt(int i, int j) { return m_dens[at(i, j)]; }
    double totalMass();

private:
    grid m_vel;
    grid m_v;
    grid m_dens;
    
    grid m_velPrev;
    grid m_vPrev;
    grid m_densPrev;
    
    double m_viscosity;
    double m_diffusion;
    double m_dt;
    
    const int m_N;
    const int m_size;               // simulation grid size (N+2) * (N+2)
    
    double m_force = 5.0;
    double m_sourceAmount = 100.0;
    

    void densityTimeStep();
    void velocityTimeStep();
    void clearPrev();
    
    int at(int i, int j){ return i * (m_N+2) + j; }
    
    void advect(int b, grid& dens, grid& densPrev, grid& vel,
                grid& visc, double dt);
    
    void project(grid& vel, grid& visc, grid& pres, grid& div);
    
    void linearSolve(int b, grid& vec, grid& vecPrev, double a, double c);
    
    void diffuse(int b, grid& vec1, grid& vec2,
                 double diffusion, double dt);
    
    void addSource(grid& vec1, grid& vec2, double dt);
    
    void setBoundry(int b, grid& vec);
    
};

#endif
