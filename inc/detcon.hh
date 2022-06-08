#pragma once

#include <utility>
#include <tuple>
#include <fstream>

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4SDManager.hh"

#include "TMath.h"

class G4VPhysicalVolume;

class G4LogicalVolume;

class detcon : public G4VUserDetectorConstruction {
public:
    detcon();
    virtual ~detcon();

    virtual G4VPhysicalVolume *Construct();

private:
    G4LogicalVolume* logicWorld = nullptr;
    G4VPhysicalVolume* physWorld = nullptr;

    G4LogicalVolume* logicAl = nullptr;
    G4VPhysicalVolume* physAl = nullptr;

    G4LogicalVolume* logicPTP = nullptr;
    G4VPhysicalVolume* physPTP = nullptr;

    G4LogicalVolume* logicDCF = nullptr;
    G4VPhysicalVolume* physDCF = nullptr;

    G4LogicalVolume* logicTPB = nullptr;
    G4VPhysicalVolume* physTPB = nullptr;

    G4LogicalVolume* logicPMT = nullptr;
    G4VPhysicalVolume* physPMT = nullptr;
};
