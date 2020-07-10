module Main where

import Criterion.Main

import Task1Bench (fastDoubleArea, fastPerimeter, slowDoubleArea, slowPerimeter)

main :: IO ()
main = do

  defaultMain
    [ bgroup "fast perimeter"   fastPerimeter
    , bgroup "slow perimeter"   slowPerimeter
    , bgroup "fast double area" fastDoubleArea
    , bgroup "slow double area" slowDoubleArea
    ]

{- local results
benchmarking fast perimeter/10^5
time                 7.089 ms   (6.433 ms .. 7.596 ms)
                     0.965 R²   (0.949 R² .. 0.980 R²)
mean                 8.510 ms   (7.936 ms .. 9.348 ms)
std dev              2.097 ms   (1.399 ms .. 2.971 ms)
variance introduced by outliers: 91% (severely inflated)

benchmarking fast perimeter/10^6
time                 131.5 ms   (80.07 ms .. 203.5 ms)
                     0.750 R²   (0.439 R² .. 0.988 R²)
mean                 108.4 ms   (84.45 ms .. 133.5 ms)
std dev              37.25 ms   (24.84 ms .. 52.42 ms)
variance introduced by outliers: 86% (severely inflated)

benchmarking fast perimeter/10^7
time                 1.097 s    (625.6 ms .. 1.566 s)
                     0.976 R²   (0.916 R² .. 1.000 R²)
mean                 769.5 ms   (606.9 ms .. 932.1 ms)
std dev              187.9 ms   (160.9 ms .. 192.3 ms)
variance introduced by outliers: 48% (moderately inflated)

benchmarking slow perimeter/10^5
time                 39.10 ms   (30.42 ms .. 62.19 ms)
                     0.485 R²   (0.309 R² .. 0.997 R²)
mean                 37.38 ms   (32.85 ms .. 54.61 ms)
std dev              16.55 ms   (1.571 ms .. 31.34 ms)
variance introduced by outliers: 93% (severely inflated)

benchmarking slow perimeter/10^6
time                 477.9 ms   (-354.8 ms .. 1.188 s)
                     0.736 R²   (0.368 R² .. NaN R²)
mean                 444.7 ms   (371.9 ms .. 579.9 ms)
std dev              132.0 ms   (9.270 ms .. 157.4 ms)
variance introduced by outliers: 73% (severely inflated)

benchmarking slow perimeter/10^7
time                 5.249 s    (3.396 s .. 6.276 s)
                     0.986 R²   (0.976 R² .. 1.000 R²)
mean                 5.624 s    (5.206 s .. 6.315 s)
std dev              679.7 ms   (230.0 ms .. 921.5 ms)
variance introduced by outliers: 23% (moderately inflated)

benchmarking fast double area/10^5
time                 5.184 ms   (4.918 ms .. 5.522 ms)
                     0.984 R²   (0.979 R² .. 0.992 R²)
mean                 5.096 ms   (4.997 ms .. 5.247 ms)
std dev              361.5 μs   (302.5 μs .. 463.4 μs)
variance introduced by outliers: 43% (moderately inflated)

benchmarking fast double area/10^6
time                 63.33 ms   (62.48 ms .. 64.25 ms)
                     1.000 R²   (0.999 R² .. 1.000 R²)
mean                 62.81 ms   (62.59 ms .. 63.16 ms)
std dev              458.5 μs   (229.4 μs .. 762.9 μs)

benchmarking fast double area/10^7
time                 803.3 ms   (-1.163 s .. 2.426 s)
                     0.590 R²   (0.199 R² .. 1.000 R²)
mean                 755.2 ms   (599.1 ms .. 1.209 s)
std dev              302.7 ms   (2.941 ms .. 354.3 ms)
variance introduced by outliers: 74% (severely inflated)

benchmarking slow double area/10^5
time                 57.26 ms   (30.21 ms .. 116.3 ms)
                     0.367 R²   (0.278 R² .. 0.994 R²)
mean                 40.81 ms   (33.19 ms .. 63.20 ms)
std dev              27.47 ms   (1.757 ms .. 50.83 ms)
variance introduced by outliers: 93% (severely inflated)

benchmarking slow double area/10^6
time                 485.9 ms   (-873.9 ms .. 1.573 s)
                     0.527 R²   (0.140 R² .. 1.000 R²)
mean                 486.0 ms   (377.2 ms .. 688.6 ms)
std dev              200.8 ms   (9.892 ms .. 239.7 ms)
variance introduced by outliers: 74% (severely inflated)

benchmarking slow double area/10^7
time                 4.130 s    (2.568 s .. 5.772 s)
                     0.980 R²   (0.960 R² .. 1.000 R²)
mean                 4.981 s    (4.547 s .. 5.414 s)
std dev              509.4 ms   (429.2 ms .. 570.7 ms)
variance introduced by outliers: 23% (moderately inflated)
-}
