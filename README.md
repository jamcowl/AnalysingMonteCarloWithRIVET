# Using [RIVET](https://rivet.hepforge.org/) to measure the non-perturbative corrections in Monte Carlo event generators

### Abstract (from [the report](MSci_Project_Report.pdf))
A method is presented for obtaining the non-perturbative correction factors from Monte Carlo event generators using the RIVET toolkit. Instead of running the generator with particular processes switched off in order to measure the necessary jet cross sections, a RIVET analysis is written which can extract these from the event record. The analysis is performed on samples (all using the AU2-CT10 tune and centre-of-mass energy √s  = 7 TeV) from three Monte Carlo generators: PYTHIA8, POWHEG1+PYTHIA8 and POWHEG2+PYTHIA8. The measured non-perturbative (NP) and parton shower (PS) correction factors for these generators are found to be in agreement with results obtained in previous studies by switching off selected processes at generator-level. These results also present an additional opportunity to study the new generator POWHEG2 and compare its non-perturbative correction factors to those of POWHEG1. The PS correction factor measured in POWHEG2 is found to be larger (by a fraction on the order of 10%) than that measured in POWHEG1 in the low p_T region (p_T  ~ 50 GeV).

### Usage

To compile a RIVET analysis, use the first argument `build` and second argument the analysis name, e.g.

`./runRivet.sh build ANALYSIS_NAME`

will build a RIVET analysis with the name `ANALYSIS_NAME`

To run a RIVET analysis, use the first argument `run` and second argument a configuration file, e.g.

`./runRivet.sh run configureRivet.py`

will run a compiled RIVET analysis on the input files specified in the `configureRivet.py` file, in the `svcMgr.EventSelector.InputCollections` list.

The existing configuration files contain filepaths specific to Monte Carlo samples stored on the UCL cluster.
