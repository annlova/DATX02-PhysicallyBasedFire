#include "FluidSolver.h"
FluidSolver::FluidSolver(int n, double diff, double visc, double dt) : m_N(n), m_diffusion(diff), m_viscosity(visc), m_dt(dt), m_size((n + 2)*(n + 2)){
    
    m_vel.resize(m_size);
    m_velPrev.resize(m_size);
    m_v.resize(m_size);
    m_vPrev.resize(m_size);
    m_dens.resize(m_size);
    m_densPrev.resize(m_size);
}
void FluidSolver::addVelocity(int i, int j, double u, double v){
    m_velPrev[at(i,j)] = m_force * u;
    m_vPrev[at(i,j)] = m_force * v;
}
void FluidSolver::addDensity(int i, int j){
    m_densPrev[at(i,j)] = m_sourceAmount;
}

void FluidSolver::clearPrev(){
    std::fill(m_densPrev.begin(), m_densPrev.end(), 0.0f);
    std::fill(m_velPrev.begin(), m_velPrev.end(), 0.0f);
    std::fill(m_vPrev.begin(), m_vPrev.end(), 0.0f);
}

// Gauss-Siedel
void FluidSolver::linearSolve(int b, grid& x, grid& x0, double a, double c){
    for (int k(0) ; k<20 ; k++ ) {
        for(int i(1); i <= m_N; i++){
            for(int j(1); j <= m_N; j++){
                x[at(i,j)] = (x0[at(i,j)] +
                a * (x[at(i-1,j)]+x[at(i+1,j)]+x[at(i,j-1)]+x[at(i,j+1)])) / c;
            }
        }
        setBoundry(b, x);
    }
}

void FluidSolver::addSource(grid& g, grid& g0, double dt){
    for(int i(0); i < m_size; i++){
        g[i] += g0[i] * dt;
    }
}


void FluidSolver::diffuse(int b, grid& g, grid &g0, double diff, double dt){
    double a = dt * diff * m_N * m_N;
    linearSolve(b, g, g0, a, 1+4*a);

}

void FluidSolver::setBoundry(int b, grid& g){
    for (int i(1) ; i <= m_N ; i++ ) {
        g[at(0  ,i)] = b==1 ? -g[at(1,i)] : g[at(1,i)];
        g[at(m_N+1,i)] = b==1 ? -g[at(m_N,i)] : g[at(m_N,i)];
        g[at(i,0  )] = b==2 ? -g[at(i,1)] : g[at(i,1)];
        g[at(i,m_N+1)] = b==2 ? -g[at(i,m_N)] : g[at(i,m_N)];
    }
    g[at(0  ,0  )] = 0.5f*(g[at(1,0  )]+g[at(0  ,1)]);
    g[at(0  ,m_N+1)] = 0.5f*(g[at(1,m_N+1)]+g[at(0  ,m_N)]);
    g[at(m_N+1,0  )] = 0.5f*(g[at(m_N,0  )]+g[at(m_N+1,1)]);
    g[at(m_N+1,m_N+1)] = 0.5f*(g[at(m_N,m_N+1)]+g[at(m_N+1,m_N)]);
}

void FluidSolver::advect(int b, grid& dens, grid& densPrev, grid& vel, grid& visc, double dt)
{
    int i0, j0, i1, j1;
    float x, y, s0, t0, s1, t1, dt0;
    
    dt0 = dt*m_N;
    for(int i(1); i <= m_N; i++){
        for(int j(1); j <= m_N; j++){
            x = i-dt0*vel[at(i,j)]; y = j-dt0*visc[at(i,j)];
            
            if (x<0.5f) {x=0.5f;} if (x>m_N+0.5f) {x=m_N+0.5f;}
            if (y<0.5f) {y=0.5f;} if (y>m_N+0.5f) {y=m_N+0.5f;}
            
            i0=(int)x; i1=i0+1;
            j0=(int)y; j1=j0+1;
            s1 = x-i0; s0 = 1-s1;
            t1 = y-j0; t0 = 1-t1;

            dens[at(i,j)] = s0*(t0*densPrev[at(i0,j0)]+t1*densPrev[at(i0,j1)])+
            s1*(t0*densPrev[at(i1,j0)]+t1*densPrev[at(i1,j1)]);
        }
    }
    setBoundry(b, dens);
}

void FluidSolver::project(grid& vel, grid& visc, grid& pres, grid& div){
    for(int i(1); i <= m_N; i++){
        for(int j(1); j <= m_N; j++){
            div[at(i,j)] = -0.5f*(vel[at(i+1,j)]-vel[at(i-1,j)]+visc[at(i,j+1)]-visc[at(i,j-1)])/m_N;
            pres[at(i,j)] = 0;
        }
    }
    setBoundry(0, div);
    setBoundry(0, pres);
    
    linearSolve(0, pres, div, 1, 4);
    
    for(int i(1); i <= m_N; i++){
        for(int j(1); j <= m_N; j++){
            vel[at(i,j)] -= 0.5f*m_N*(pres[at(i+1,j)]-pres[at(i-1,j)]);
            visc[at(i,j)] -= 0.5f*m_N*(pres[at(i,j+1)]-pres[at(i,j-1)]);
        }
    }
    setBoundry(1, vel);
    setBoundry(2, visc);
}

void FluidSolver::timeStep(){
    densityTimeStep();
    velocityTimeStep();
    clearPrev();
}


void FluidSolver::densityTimeStep(){
    addSource (m_dens, m_densPrev, m_dt); // replace with a source grid?
    m_dens.swap(m_densPrev); // since the new source will be added again
    diffuse (0, m_dens, m_densPrev, m_diffusion, m_dt ); // here
    m_dens.swap(m_densPrev);
    advect (0, m_dens, m_densPrev, m_vel, m_v, m_dt );
}

void FluidSolver::velocityTimeStep (){
    
    addSource(m_vel, m_velPrev, m_dt);
    addSource(m_v, m_vPrev, m_dt);
    
    m_vel.swap(m_velPrev);
    diffuse(1, m_vel, m_velPrev, m_viscosity, m_dt);
    
    m_v.swap(m_vPrev);
    diffuse(2, m_v, m_vPrev, m_viscosity, m_dt);
    
    project(m_vel, m_v, m_velPrev, m_vPrev);
    
    m_vel.swap(m_velPrev);
    m_v.swap(m_vPrev);
    
    advect(1, m_vel, m_velPrev, m_velPrev, m_vPrev, m_dt);
    advect(2, m_v, m_vPrev, m_velPrev, m_vPrev, m_dt);
    
    project(m_vel, m_v, m_velPrev, m_vPrev);
}

double FluidSolver::totalMass(){
    double m = 0.0;
    for(auto cell : m_dens){
        m += cell;
    }
    return m;
}


FluidSolver::~FluidSolver(){
    
}

