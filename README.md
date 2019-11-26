# social-transit-trial-driver

A driver for running batches of test cases through the main solver for a research project of mine dealing with public transit design with social access objectives.

This program is meant to act as a driver for running the main solution algorithm [social-transit-solver](https://github.com/adam-rumpf/social-transit-solver) repeatedly for different sets of input files. See the main solver's README for a full description of its input file format, and see its release page for an executable version. The driver, itself, requires an input file [`trials.txt`](#trialstxt) to specify the set of trials to be run, and outputs a file [`log.txt`](#logtxt) containing a log of the trial execution results.

## File Structure

This program should be placed in a folder alongsidee an executable version of the main solution algorithm, `social_transit_solver.exe`. For every trial that is being run, there should be a separate folder. The locations of the trial folders do not matter, but they should be somewhere whose file path is known. Within each trial folder there should be a `data/` and `log/` folder, both filled with any necessary input files as described by the [social-transit-solver](https://github.com/adam-rumpf/social-transit-solver) README.

## `trials.txt`

A file called `trials.txt` should be placed in the same directory as this program. It is meant to specify a list of the trials to be run. Specifically, each row specifies the file path to one of the trial folders, and then the trial driver will call the main solver to run through the solution process using those `data/` and `log/` folders.

The trial file is arranged as a tab-separated list. After an initial comment line, each row should contain the following columns:
 * `ID`: ID number of trial. Simply acts as a label to match the trial file contents with the output log.
 * `root`: The file path to one of the trial directories. This will be passed as a command line argument to the main solver, which will then look for `data/` and `log/` within that directory.

## `log.txt`

An output log file will be produced by the trial driver in its current directory. The log contains a row to summarize the results of each trial. Note that the solution algorithm's outputs will still be located within the trial directories and thus must be retrieved manually.

After an initial comment line, each row contains the following columns:
 * `ID`: ID number of trial. Corresponds to the ID from the trial file corresponding to this row's trial.
 * `exit`: Exit code produced by the main solver upon termination.
 * `time`: Total time spent on the trial, in HH:MM:SS format.
