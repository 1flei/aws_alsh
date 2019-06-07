# Sublinear Time Nearest Neighbor Search over Generalized Weighted Space

Paper accepted by ICML 2019
**Sublinear Time Nearest Neighbor Search over Generalized Weighted Space. ICML 2019: 3773-3781, Yifan Lei, Qiang Huang, Mohan S. Kankanhalli, Anthony K. H. Tung**

To build the project, use the following instructions:

```
mkdir build
cd build
cmake ..
make -j
```

Then run 
```
./alsh --help
```
for help information.

A possible example to run could be:
```
./alsh -A fraction_recall_s2alsh -n 60000 -q 1000 -d 784 -D ../data/Mnist784/Mnist784.ds -Q ../data/Mnist784/Mnist784.q -W ../data/Mnist784/Mnist784_normal.w -G ../data/Mnist784/Mnist784_normal.gt -O output.out -U 3.140000 --data_hash_filename data_hash.dh --query_hash_filename query_hash.qh
```

The python scripts on scripts folder can be used to run the automatically run the precision_recall and fraction_recall experiments, e.g.
```
python ../scripts/run_ground_truth.py
```
```
python ../scripts/run_precision_recall.py
```
```
python ../scripts/run_fraction_recall.py
```

In order to run the scripts, the datasets/query should be put in the ./data folder, or the "./scripts/dataset_config.py" should be modified accordingly.
[Datasets link via onedrive](https://1drv.ms/u/s!Ascf3jEjrVdxgvAsrTrUdH2G5p0-wg?e=pgN5j0)


For more information, please contact leiyifan@u.nus.edu