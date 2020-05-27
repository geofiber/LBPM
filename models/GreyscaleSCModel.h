/*
Implementation of color lattice boltzmann model
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <fstream>

#include "common/Communication.h"
#include "common/MPI.h"
#include "common/Database.h"
#include "common/ScaLBL.h"
#include "ProfilerApp.h"
#include "threadpool/thread_pool.h"

class ScaLBL_GreyscaleSCModel{
public:
	ScaLBL_GreyscaleSCModel(int RANK, int NP, MPI_Comm COMM);
	~ScaLBL_GreyscaleSCModel();	
	
	// functions in they should be run
	void ReadParams(string filename);
	void ReadParams(std::shared_ptr<Database> db0);
	void SetDomain();
	void ReadInput();
	void Create();
	void Initialize();
	void Run();
	void WriteDebug();
	void WriteOutput();
	
	bool Restart,pBC;
	int timestep,timestepMax;
	int BoundaryCondition;
    int CollisionType;
	double tauA,tauB;
    double tauA_eff,tauB_eff;
    double Gsc;
    double rhoA,rhoB;
    double rhoA_minor,rhoB_minor;//dissolved density
	double tolerance;
	double Fx,Fy,Fz,flux;
	double dinA,doutA;
	double dinB,doutB;
    double GreyPorosity;
	
	int Nx,Ny,Nz,N,Np;
	int rank,nprocx,nprocy,nprocz,nprocs;
	double Lx,Ly,Lz;

	std::shared_ptr<Domain> Dm;   // this domain is for analysis
	std::shared_ptr<Domain> Mask; // this domain is for lbm
	std::shared_ptr<ScaLBL_Communicator> ScaLBL_Comm;
	std::shared_ptr<ScaLBL_Communicator> ScaLBL_Comm_Regular;
    
    // input database
    std::shared_ptr<Database> db;
    std::shared_ptr<Database> domain_db;
    std::shared_ptr<Database> greyscaleSC_db;
    std::shared_ptr<Database> analysis_db;
    std::shared_ptr<Database> vis_db;

    signed char *id;    
	int *NeighborList;
    int *dvcMap;
	double *fqA, *fqB;
	double *Permeability;//grey voxel permeability
    //double relPermA,relPermB;//grey voxel relperm
	double *Porosity;
	double *Velocity;
	double *Pressure_dvc;
    double *DenA, *DenB;
    double *DenGradA,*DenGradB;
    double *SolidForceA,*SolidForceB;
    
    IntArray Map;
    DoubleArray SignDist;
    DoubleArray Velocity_x;
    DoubleArray Velocity_y;
    DoubleArray Velocity_z;
    DoubleArray PorosityMap;
    DoubleArray Pressure;
    DoubleArray DenA_data;
    DoubleArray DenB_data;
		
private:
	MPI_Comm comm;
    
	int dist_mem_size;
	int neighborSize;
	// filenames
    char LocalRankString[8];
    char LocalRankFilename[40];
    char LocalRestartFile[40];
   
    void AssignGreyscaleAndSolidLabels();
    void Density_Init();   
};

