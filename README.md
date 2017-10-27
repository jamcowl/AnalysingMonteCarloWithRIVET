# Using [RIVET](https://rivet.hepforge.org/) to measure the nonperturbative corrections in Monte Carlo event generators

This was the title of my final year MSci physics project in the [UCL ATLAS group](https://www.hep.ucl.ac.uk/atlas/). More detail is available in the [project report](MSci_Project_Report.pdf).

### Technical info

How to use the `runRivet.sh` script:

To compile a RIVET analysis, use the first argument `build` and second argument the analysis name, e.g.

`./runRivet.sh build ANALYSIS_NAME`

will build a RIVET analysis with the name `ANALYSIS_NAME`

To run a RIVET analysis, use the first argument `run` and second argument a configuration file, e.g.

`./runRivet.sh run configureRivet.py`

will run a compiled RIVET analysis on the input files specified in the `configureRivet.py` file, in the `svcMgr.EventSelector.InputCollections` list.

The existing `configureRivet.py` filepaths are specific to Monte Carlo samples stored on the UCL cluster.
