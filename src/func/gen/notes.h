#ifndef CSYNTH_NOTES_H
#define CSYNTH_NOTES_H

#include "./const.h"

/*
 * Note constants for 10 octaves of 12 notes equal temperament. The contents of
 * this file can be generated using `utils/notes.c`.
 */

#define C0_ 16.351597831287413953  // 440 * pow(2, -57 / 12.0)
#define Cs0_ 17.323914436054504762 // 440 * pow(2, -56 / 12.0)
#define Db0_ 17.323914436054504762 // 440 * pow(2, -56 / 12.0)
#define D0_ 18.354047994837976887  // 440 * pow(2, -55 / 12.0)
#define Ds0_ 19.445436482630057640 // 440 * pow(2, -54 / 12.0)
#define Eb0_ 19.445436482630057640 // 440 * pow(2, -54 / 12.0)
#define E0_ 20.601722307054366468  // 440 * pow(2, -53 / 12.0)
#define F0_ 21.826764464562746326  // 440 * pow(2, -52 / 12.0)
#define Fs0_ 23.124651419477149972 // 440 * pow(2, -51 / 12.0)
#define Gb0_ 23.124651419477149972 // 440 * pow(2, -51 / 12.0)
#define G0_ 24.499714748859325653  // 440 * pow(2, -50 / 12.0)
#define Gs0_ 25.956543598746574020 // 440 * pow(2, -49 / 12.0)
#define Ab0_ 25.956543598746574020 // 440 * pow(2, -49 / 12.0)
#define A0_ 27.500000000000000000  // 440 * pow(2, -48 / 12.0)
#define As0_ 29.135235094880620466 // 440 * pow(2, -47 / 12.0)
#define Bb0_ 29.135235094880620466 // 440 * pow(2, -47 / 12.0)
#define B0_ 30.867706328507750868  // 440 * pow(2, -46 / 12.0)
#define C1_ 32.703195662574827907  // 440 * pow(2, -45 / 12.0)
#define Cs1_ 34.647828872109009524 // 440 * pow(2, -44 / 12.0)
#define Db1_ 34.647828872109009524 // 440 * pow(2, -44 / 12.0)
#define D1_ 36.708095989675939563  // 440 * pow(2, -43 / 12.0)
#define Ds1_ 38.890872965260115279 // 440 * pow(2, -42 / 12.0)
#define Eb1_ 38.890872965260115279 // 440 * pow(2, -42 / 12.0)
#define E1_ 41.203444614108747146  // 440 * pow(2, -41 / 12.0)
#define F1_ 43.653528929125485547  // 440 * pow(2, -40 / 12.0)
#define Fs1_ 46.249302838954299943 // 440 * pow(2, -39 / 12.0)
#define Gb1_ 46.249302838954299943 // 440 * pow(2, -39 / 12.0)
#define G1_ 48.999429497718665516  // 440 * pow(2, -38 / 12.0)
#define Gs1_ 51.913087197493140934 // 440 * pow(2, -37 / 12.0)
#define Ab1_ 51.913087197493140934 // 440 * pow(2, -37 / 12.0)
#define A1_ 55.000000000000000000  // 440 * pow(2, -36 / 12.0)
#define As1_ 58.270470189761240931 // 440 * pow(2, -35 / 12.0)
#define Bb1_ 58.270470189761240931 // 440 * pow(2, -35 / 12.0)
#define B1_ 61.735412657015501736  // 440 * pow(2, -34 / 12.0)
#define C2_ 65.406391325149655813  // 440 * pow(2, -33 / 12.0)
#define Cs2_ 69.295657744218019047 // 440 * pow(2, -32 / 12.0)
#define Db2_ 69.295657744218019047 // 440 * pow(2, -32 / 12.0)
#define D2_ 73.416191979351879127  // 440 * pow(2, -31 / 12.0)
#define Ds2_ 77.781745930520230559 // 440 * pow(2, -30 / 12.0)
#define Eb2_ 77.781745930520230559 // 440 * pow(2, -30 / 12.0)
#define E2_ 82.406889228217494292  // 440 * pow(2, -29 / 12.0)
#define F2_ 87.307057858250971094  // 440 * pow(2, -28 / 12.0)
#define Fs2_ 92.498605677908599887 // 440 * pow(2, -27 / 12.0)
#define Gb2_ 92.498605677908599887 // 440 * pow(2, -27 / 12.0)
#define G2_ 97.998858995437331032  // 440 * pow(2, -26 / 12.0)
#define Gs2_ 103.82617439498628187 // 440 * pow(2, -25 / 12.0)
#define Ab2_ 103.82617439498628187 // 440 * pow(2, -25 / 12.0)
#define A2_ 110.00000000000000000  // 440 * pow(2, -24 / 12.0)
#define As2_ 116.54094037952248186 // 440 * pow(2, -23 / 12.0)
#define Bb2_ 116.54094037952248186 // 440 * pow(2, -23 / 12.0)
#define B2_ 123.47082531403103189  // 440 * pow(2, -22 / 12.0)
#define C3_ 130.81278265029931163  // 440 * pow(2, -21 / 12.0)
#define Cs3_ 138.59131548843603809 // 440 * pow(2, -20 / 12.0)
#define Db3_ 138.59131548843603809 // 440 * pow(2, -20 / 12.0)
#define D3_ 146.83238395870378667  // 440 * pow(2, -19 / 12.0)
#define Ds3_ 155.56349186104046112 // 440 * pow(2, -18 / 12.0)
#define Eb3_ 155.56349186104046112 // 440 * pow(2, -18 / 12.0)
#define E3_ 164.81377845643496016  // 440 * pow(2, -17 / 12.0)
#define F3_ 174.61411571650194219  // 440 * pow(2, -16 / 12.0)
#define Fs3_ 184.99721135581719977 // 440 * pow(2, -15 / 12.0)
#define Gb3_ 184.99721135581719977 // 440 * pow(2, -15 / 12.0)
#define G3_ 195.99771799087463364  // 440 * pow(2, -14 / 12.0)
#define Gs3_ 207.65234878997256374 // 440 * pow(2, -13 / 12.0)
#define Ab3_ 207.65234878997256374 // 440 * pow(2, -13 / 12.0)
#define A3_ 220.00000000000000000  // 440 * pow(2, -12 / 12.0)
#define As3_ 233.08188075904496372 // 440 * pow(2, -11 / 12.0)
#define Bb3_ 233.08188075904496372 // 440 * pow(2, -11 / 12.0)
#define B3_ 246.94165062806206379  // 440 * pow(2, -10 / 12.0)
#define C4_ 261.62556530059862325  // 440 * pow(2, -9 / 12.0)
#define Cs4_ 277.18263097687207619 // 440 * pow(2, -8 / 12.0)
#define Db4_ 277.18263097687207619 // 440 * pow(2, -8 / 12.0)
#define D4_ 293.66476791740757335  // 440 * pow(2, -7 / 12.0)
#define Ds4_ 311.12698372208092223 // 440 * pow(2, -6 / 12.0)
#define Eb4_ 311.12698372208092223 // 440 * pow(2, -6 / 12.0)
#define E4_ 329.62755691286992032  // 440 * pow(2, -5 / 12.0)
#define F4_ 349.22823143300388438  // 440 * pow(2, -4 / 12.0)
#define Fs4_ 369.99442271163439955 // 440 * pow(2, -3 / 12.0)
#define Gb4_ 369.99442271163439955 // 440 * pow(2, -3 / 12.0)
#define G4_ 391.99543598174926728  // 440 * pow(2, -2 / 12.0)
#define Gs4_ 415.30469757994512747 // 440 * pow(2, -1 / 12.0)
#define Ab4_ 415.30469757994512747 // 440 * pow(2, -1 / 12.0)
#define A4_ 440.00000000000000000  // 440 * pow(2, 0 / 12.0)
#define As4_ 466.16376151808992745 // 440 * pow(2, 1 / 12.0)
#define Bb4_ 466.16376151808992745 // 440 * pow(2, 1 / 12.0)
#define B4_ 493.88330125612412758  // 440 * pow(2, 2 / 12.0)
#define C5_ 523.25113060119724651  // 440 * pow(2, 3 / 12.0)
#define Cs5_ 554.36526195374415238 // 440 * pow(2, 4 / 12.0)
#define Db5_ 554.36526195374415238 // 440 * pow(2, 4 / 12.0)
#define D5_ 587.32953583481514670  // 440 * pow(2, 5 / 12.0)
#define Ds5_ 622.25396744416184447 // 440 * pow(2, 6 / 12.0)
#define Eb5_ 622.25396744416184447 // 440 * pow(2, 6 / 12.0)
#define E5_ 659.25511382573984065  // 440 * pow(2, 7 / 12.0)
#define F5_ 698.45646286600776875  // 440 * pow(2, 8 / 12.0)
#define Fs5_ 739.98884542326879910 // 440 * pow(2, 9 / 12.0)
#define Gb5_ 739.98884542326879910 // 440 * pow(2, 9 / 12.0)
#define G5_ 783.99087196349853457  // 440 * pow(2, 10 / 12.0)
#define Gs5_ 830.60939515989025494 // 440 * pow(2, 11 / 12.0)
#define Ab5_ 830.60939515989025494 // 440 * pow(2, 11 / 12.0)
#define A5_ 880.00000000000000000  // 440 * pow(2, 12 / 12.0)
#define As5_ 932.32752303617985490 // 440 * pow(2, 13 / 12.0)
#define Bb5_ 932.32752303617985490 // 440 * pow(2, 13 / 12.0)
#define B5_ 987.76660251224825515  // 440 * pow(2, 14 / 12.0)
#define C6_ 1046.5022612023944930  // 440 * pow(2, 15 / 12.0)
#define Cs6_ 1108.7305239074883048 // 440 * pow(2, 16 / 12.0)
#define Db6_ 1108.7305239074883048 // 440 * pow(2, 16 / 12.0)
#define D6_ 1174.6590716696302934  // 440 * pow(2, 17 / 12.0)
#define Ds6_ 1244.5079348883236889 // 440 * pow(2, 18 / 12.0)
#define Eb6_ 1244.5079348883236889 // 440 * pow(2, 18 / 12.0)
#define E6_ 1318.5102276514796813  // 440 * pow(2, 19 / 12.0)
#define F6_ 1396.9129257320155375  // 440 * pow(2, 20 / 12.0)
#define Fs6_ 1479.9776908465375982 // 440 * pow(2, 21 / 12.0)
#define Gb6_ 1479.9776908465375982 // 440 * pow(2, 21 / 12.0)
#define G6_ 1567.9817439269970691  // 440 * pow(2, 22 / 12.0)
#define Gs6_ 1661.2187903197805099 // 440 * pow(2, 23 / 12.0)
#define Ab6_ 1661.2187903197805099 // 440 * pow(2, 23 / 12.0)
#define A6_ 1760.0000000000000000  // 440 * pow(2, 24 / 12.0)
#define As6_ 1864.6550460723597098 // 440 * pow(2, 25 / 12.0)
#define Bb6_ 1864.6550460723597098 // 440 * pow(2, 25 / 12.0)
#define B6_ 1975.5332050244960556  // 440 * pow(2, 26 / 12.0)
#define C7_ 2093.0045224047889860  // 440 * pow(2, 27 / 12.0)
#define Cs7_ 2217.4610478149766095 // 440 * pow(2, 28 / 12.0)
#define Db7_ 2217.4610478149766095 // 440 * pow(2, 28 / 12.0)
#define D7_ 2349.3181433392601321  // 440 * pow(2, 29 / 12.0)
#define Ds7_ 2489.0158697766473779 // 440 * pow(2, 30 / 12.0)
#define Eb7_ 2489.0158697766473779 // 440 * pow(2, 30 / 12.0)
#define E7_ 2637.0204553029598173  // 440 * pow(2, 31 / 12.0)
#define F7_ 2793.8258514640310750  // 440 * pow(2, 32 / 12.0)
#define Fs7_ 2959.9553816930751964 // 440 * pow(2, 33 / 12.0)
#define Gb7_ 2959.9553816930751964 // 440 * pow(2, 33 / 12.0)
#define G7_ 3135.9634878539945930  // 440 * pow(2, 34 / 12.0)
#define Gs7_ 3322.4375806395610198 // 440 * pow(2, 35 / 12.0)
#define Ab7_ 3322.4375806395610198 // 440 * pow(2, 35 / 12.0)
#define A7_ 3520.0000000000000000  // 440 * pow(2, 36 / 12.0)
#define As7_ 3729.3100921447194196 // 440 * pow(2, 37 / 12.0)
#define Bb7_ 3729.3100921447194196 // 440 * pow(2, 37 / 12.0)
#define B7_ 3951.0664100489921111  // 440 * pow(2, 38 / 12.0)
#define C8_ 4186.0090448095779720  // 440 * pow(2, 39 / 12.0)
#define Cs8_ 4434.9220956299532190 // 440 * pow(2, 40 / 12.0)
#define Db8_ 4434.9220956299532190 // 440 * pow(2, 40 / 12.0)
#define D8_ 4698.6362866785202641  // 440 * pow(2, 41 / 12.0)
#define Ds8_ 4978.0317395532947558 // 440 * pow(2, 42 / 12.0)
#define Eb8_ 4978.0317395532947558 // 440 * pow(2, 42 / 12.0)
#define E8_ 5274.0409106059196347  // 440 * pow(2, 43 / 12.0)
#define F8_ 5587.6517029280621500  // 440 * pow(2, 44 / 12.0)
#define Fs8_ 5919.9107633861503928 // 440 * pow(2, 45 / 12.0)
#define Gb8_ 5919.9107633861503928 // 440 * pow(2, 45 / 12.0)
#define G8_ 6271.9269757079891860  // 440 * pow(2, 46 / 12.0)
#define Gs8_ 6644.8751612791220396 // 440 * pow(2, 47 / 12.0)
#define Ab8_ 6644.8751612791220396 // 440 * pow(2, 47 / 12.0)
#define A8_ 7040.0000000000000000  // 440 * pow(2, 48 / 12.0)
#define As8_ 7458.6201842894370202 // 440 * pow(2, 49 / 12.0)
#define Bb8_ 7458.6201842894370202 // 440 * pow(2, 49 / 12.0)
#define B8_ 7902.1328200979878602  // 440 * pow(2, 50 / 12.0)
#define C9_ 8372.0180896191559441  // 440 * pow(2, 51 / 12.0)
#define Cs9_ 8869.8441912599064381 // 440 * pow(2, 52 / 12.0)
#define Db9_ 8869.8441912599064381 // 440 * pow(2, 52 / 12.0)
#define D9_ 9397.2725733570441662  // 440 * pow(2, 53 / 12.0)
#define Ds9_ 9956.0634791065895115 // 440 * pow(2, 54 / 12.0)
#define Eb9_ 9956.0634791065895115 // 440 * pow(2, 54 / 12.0)
#define E9_ 10548.081821211835631  // 440 * pow(2, 55 / 12.0)
#define F9_ 11175.303405856126119  // 440 * pow(2, 56 / 12.0)
#define Fs9_ 11839.821526772300786 // 440 * pow(2, 57 / 12.0)
#define Gb9_ 11839.821526772300786 // 440 * pow(2, 57 / 12.0)
#define G9_ 12543.853951415974734  // 440 * pow(2, 58 / 12.0)
#define Gs9_ 13289.750322558245898 // 440 * pow(2, 59 / 12.0)
#define Ab9_ 13289.750322558245898 // 440 * pow(2, 59 / 12.0)
#define A9_ 14080.000000000000000  // 440 * pow(2, 60 / 12.0)
#define As9_ 14917.240368578874040 // 440 * pow(2, 61 / 12.0)
#define Bb9_ 14917.240368578874040 // 440 * pow(2, 61 / 12.0)
#define B9_ 15804.265640195975720  // 440 * pow(2, 62 / 12.0)

#define C0 (const_(C0_))
#define Cs0 (const_(Cs0_))
#define Db0 (const_(Db0_))
#define D0 (const_(D0_))
#define Ds0 (const_(Ds0_))
#define Eb0 (const_(Eb0_))
#define E0 (const_(E0_))
#define F0 (const_(F0_))
#define Fs0 (const_(Fs0_))
#define Gb0 (const_(Gb0_))
#define G0 (const_(G0_))
#define Gs0 (const_(Gs0_))
#define Ab0 (const_(Ab0_))
#define A0 (const_(A0_))
#define As0 (const_(As0_))
#define Bb0 (const_(Bb0_))
#define B0 (const_(B0_))
#define C1 (const_(C1_))
#define Cs1 (const_(Cs1_))
#define Db1 (const_(Db1_))
#define D1 (const_(D1_))
#define Ds1 (const_(Ds1_))
#define Eb1 (const_(Eb1_))
#define E1 (const_(E1_))
#define F1 (const_(F1_))
#define Fs1 (const_(Fs1_))
#define Gb1 (const_(Gb1_))
#define G1 (const_(G1_))
#define Gs1 (const_(Gs1_))
#define Ab1 (const_(Ab1_))
#define A1 (const_(A1_))
#define As1 (const_(As1_))
#define Bb1 (const_(Bb1_))
#define B1 (const_(B1_))
#define C2 (const_(C2_))
#define Cs2 (const_(Cs2_))
#define Db2 (const_(Db2_))
#define D2 (const_(D2_))
#define Ds2 (const_(Ds2_))
#define Eb2 (const_(Eb2_))
#define E2 (const_(E2_))
#define F2 (const_(F2_))
#define Fs2 (const_(Fs2_))
#define Gb2 (const_(Gb2_))
#define G2 (const_(G2_))
#define Gs2 (const_(Gs2_))
#define Ab2 (const_(Ab2_))
#define A2 (const_(A2_))
#define As2 (const_(As2_))
#define Bb2 (const_(Bb2_))
#define B2 (const_(B2_))
#define C3 (const_(C3_))
#define Cs3 (const_(Cs3_))
#define Db3 (const_(Db3_))
#define D3 (const_(D3_))
#define Ds3 (const_(Ds3_))
#define Eb3 (const_(Eb3_))
#define E3 (const_(E3_))
#define F3 (const_(F3_))
#define Fs3 (const_(Fs3_))
#define Gb3 (const_(Gb3_))
#define G3 (const_(G3_))
#define Gs3 (const_(Gs3_))
#define Ab3 (const_(Ab3_))
#define A3 (const_(A3_))
#define As3 (const_(As3_))
#define Bb3 (const_(Bb3_))
#define B3 (const_(B3_))
#define C4 (const_(C4_))
#define Cs4 (const_(Cs4_))
#define Db4 (const_(Db4_))
#define D4 (const_(D4_))
#define Ds4 (const_(Ds4_))
#define Eb4 (const_(Eb4_))
#define E4 (const_(E4_))
#define F4 (const_(F4_))
#define Fs4 (const_(Fs4_))
#define Gb4 (const_(Gb4_))
#define G4 (const_(G4_))
#define Gs4 (const_(Gs4_))
#define Ab4 (const_(Ab4_))
#define A4 (const_(A4_))
#define As4 (const_(As4_))
#define Bb4 (const_(Bb4_))
#define B4 (const_(B4_))
#define C5 (const_(C5_))
#define Cs5 (const_(Cs5_))
#define Db5 (const_(Db5_))
#define D5 (const_(D5_))
#define Ds5 (const_(Ds5_))
#define Eb5 (const_(Eb5_))
#define E5 (const_(E5_))
#define F5 (const_(F5_))
#define Fs5 (const_(Fs5_))
#define Gb5 (const_(Gb5_))
#define G5 (const_(G5_))
#define Gs5 (const_(Gs5_))
#define Ab5 (const_(Ab5_))
#define A5 (const_(A5_))
#define As5 (const_(As5_))
#define Bb5 (const_(Bb5_))
#define B5 (const_(B5_))
#define C6 (const_(C6_))
#define Cs6 (const_(Cs6_))
#define Db6 (const_(Db6_))
#define D6 (const_(D6_))
#define Ds6 (const_(Ds6_))
#define Eb6 (const_(Eb6_))
#define E6 (const_(E6_))
#define F6 (const_(F6_))
#define Fs6 (const_(Fs6_))
#define Gb6 (const_(Gb6_))
#define G6 (const_(G6_))
#define Gs6 (const_(Gs6_))
#define Ab6 (const_(Ab6_))
#define A6 (const_(A6_))
#define As6 (const_(As6_))
#define Bb6 (const_(Bb6_))
#define B6 (const_(B6_))
#define C7 (const_(C7_))
#define Cs7 (const_(Cs7_))
#define Db7 (const_(Db7_))
#define D7 (const_(D7_))
#define Ds7 (const_(Ds7_))
#define Eb7 (const_(Eb7_))
#define E7 (const_(E7_))
#define F7 (const_(F7_))
#define Fs7 (const_(Fs7_))
#define Gb7 (const_(Gb7_))
#define G7 (const_(G7_))
#define Gs7 (const_(Gs7_))
#define Ab7 (const_(Ab7_))
#define A7 (const_(A7_))
#define As7 (const_(As7_))
#define Bb7 (const_(Bb7_))
#define B7 (const_(B7_))
#define C8 (const_(C8_))
#define Cs8 (const_(Cs8_))
#define Db8 (const_(Db8_))
#define D8 (const_(D8_))
#define Ds8 (const_(Ds8_))
#define Eb8 (const_(Eb8_))
#define E8 (const_(E8_))
#define F8 (const_(F8_))
#define Fs8 (const_(Fs8_))
#define Gb8 (const_(Gb8_))
#define G8 (const_(G8_))
#define Gs8 (const_(Gs8_))
#define Ab8 (const_(Ab8_))
#define A8 (const_(A8_))
#define As8 (const_(As8_))
#define Bb8 (const_(Bb8_))
#define B8 (const_(B8_))
#define C9 (const_(C9_))
#define Cs9 (const_(Cs9_))
#define Db9 (const_(Db9_))
#define D9 (const_(D9_))
#define Ds9 (const_(Ds9_))
#define Eb9 (const_(Eb9_))
#define E9 (const_(E9_))
#define F9 (const_(F9_))
#define Fs9 (const_(Fs9_))
#define Gb9 (const_(Gb9_))
#define G9 (const_(G9_))
#define Gs9 (const_(Gs9_))
#define Ab9 (const_(Ab9_))
#define A9 (const_(A9_))
#define As9 (const_(As9_))
#define Bb9 (const_(Bb9_))
#define B9 (const_(B9_))

#endif // CSYNTH_NOTES_H
