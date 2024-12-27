/*
 *     ______ ______ _   _ _    _           _     ___  _  _
 *    |  ____|  ____| \ | | |  | |         | |   |__ \| || |
 *    | |__  | |__  |  \| | |__| | __ _ ___| |__    ) | || |_
 *    |  __| |  __| | . ` |  __  |/ _` / __| '_ \  / /|__   _|
 *    | |____| |    | |\  | |  | | (_| \__ \ | | |/ /_   | |
 *    |______|_|    |_| \_|_|  |_|\__,_|___/_| |_|____|  |_|
 *
 *                __                        __         ___           __                                               __                               __    _         __              __      ___                 __   _
 *     ___ __ __ / /_ ____ ___  __ _  ___  / /__ __   / _/___ _ ___ / /_   ___  ___   ___  ____ ____ ____ __ __ ___  / /_ ___  ___ _ ____ ___ _ ___   / /   (_)____   / /  ___ _ ___  / /     / _/__ __ ___  ____ / /_ (_)___   ___
 *    / -_)\ \ // __// __// -_)/  ' \/ -_)/ // // /  / _// _ `/(_-</ __/  / _ \/ _ \ / _ \/___// __// __// // // _ \/ __// _ \/ _ `// __// _ `// _ \ / _ \ / // __/  / _ \/ _ `/(_-< / _ \   / _// // // _ \/ __// __// // _ \ / _ \
 *    \__//_\_\ \__//_/   \__//_/_/_/\__//_/ \_, /  /_/  \_,_//___/\__/  /_//_/\___//_//_/     \__//_/   \_, // .__/\__/ \___/\_, //_/   \_,_// .__//_//_//_/ \__/  /_//_/\_,_//___//_//_/  /_/  \_,_//_//_/\__/ \__//_/ \___//_//_/
 *                                          /___/                                                       /___//_/             /___/           /_/
 *
 *     MIT License
 *
 *     Copyright (c) 2024 Warren Austin (EFNHash24)
 *
 *     Permission is hereby granted, free of charge, to any person obtaining a copy
 *     of this software and associated documentation files (the "Software"), to deal
 *     in the Software without restriction, including without limitation the rights
 *     to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *     copies of the Software, and to permit persons to whom the Software is
 *     furnished to do so, subject to the following conditions:
 *
 *     The above copyright notice and this permission notice shall be included in all
 *     copies or substantial portions of the Software.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *     IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *     FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *     AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *     LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *     OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *     SOFTWARE.
 * 
 *      _  __      ___   ___ _  _ ___ _  _  ___   _ 
 *     | | \ \    / /_\ | _ \ \| |_ _| \| |/ __| | |
 *     |_|  \ \/\/ / _ \|   / .` || || .` | (_ | |_|
 *     (_)   \_/\_/_/ \_\_|_\_|\_|___|_|\_|\___| (_)
 *                                                 
 *     THIS IS A RUSHED ATTEMPT AT A FULL LIBRARY. EXPECT MORE IN THE FUTURE. THIS ONLY
 *     INCLUDES THE BARE NECESSITIES TO FUNCTION PROPERLY.
 *
 *     Currently, this library provides the core hashing functionality that is essential for
 *     its basic use cases. It includes basic hash operations on blocks of data and simple
 *     variants for customizable parameters and hash computations. Expect more features,
 *     optimizations, and utility functions to be added in future releases.
 *
 *     Future Updates:
 *     - Performance optimizations: Further improvements to hashing speed and memory usage.
 *     - New hashing variants: Including support for different block sizes, and better
 *       collision resistance.
 *     - Streaming support: Methods for hashing large data streams incrementally.
 *     - Integration with other hashing libraries: Support for interfacing with common
 *       libraries and APIs.
 *     - Extensive error handling and debugging: To make the library more robust and easier to use.
 *     - Documentation: Comprehensive documentation for both users and developers.
 *
 */

namespace efn24 {
    enum EFNHASH_VERSION_TAGS : int {
        STABLE = 2, LATEST = 1, DEVELOPMENT = 3,
    };

    const EFNHASH_VERSION_TAGS efnhash_version_tag = EFNHASH_VERSION_TAGS::STABLE;
    const unsigned int efnhash_version_major = 1;
    const unsigned int efnhash_version_minor = 0;
    const unsigned int efnhash_version_patch = 0;

    const char* efnhash_version_string = "EFNHASH$1.0.0 (EFN24 R1 STABLE)";

    typedef unsigned long long efnhash64_uint_length;
    typedef unsigned long long efnhash64_uint_size;
    typedef unsigned long long efnhash64_uint_64;
    typedef unsigned long long efnhash64_digest;
    typedef unsigned long long efnhash64_block_size;
    typedef unsigned long long efnhash64_accumulator_size;

    const unsigned long long p1 = 0xc13fa9a902a6328f;
    const unsigned long long p2 = 0xbf58476d1ce4e5b9;
    const unsigned long long p3 = 0x94d049bb133111eb;
    const unsigned long long p4 = 0x2545f4914f6cdd1d;
    const unsigned long long acc_default = 0xcbf29ce484222325;

    inline efnhash64_digest efnhash64(efnhash64_block_size* data, efnhash64_uint_length data_length) {
        efnhash64_accumulator_size accumulator = acc_default;

        accumulator *= data_length;

        for (efnhash64_uint_length i = 0; i + 7 < data_length; i += 8) {
            efnhash64_block_size iter_data1 = data[i];
            efnhash64_block_size iter_data2 = data[i + 1];
            efnhash64_block_size iter_data3 = data[i + 2];
            efnhash64_block_size iter_data4 = data[i + 3];
            efnhash64_block_size iter_data5 = data[i + 4];
            efnhash64_block_size iter_data6 = data[i + 5];
            efnhash64_block_size iter_data7 = data[i + 6];
            efnhash64_block_size iter_data8 = data[i + 7];

            accumulator ^= iter_data1;
            accumulator ^= iter_data2;
            accumulator ^= iter_data3;
            accumulator ^= iter_data4;
            accumulator ^= iter_data5;
            accumulator ^= iter_data6;
            accumulator ^= iter_data7;
            accumulator ^= iter_data8;

            accumulator *= p1;
            accumulator ^= (accumulator >> 33);
        }

        for (efnhash64_uint_length i = data_length / 8 * 8; i + 3 < data_length; i += 4) {
            efnhash64_block_size iter_data1 = data[i];
            efnhash64_block_size iter_data2 = data[i + 1];
            efnhash64_block_size iter_data3 = data[i + 2];
            efnhash64_block_size iter_data4 = data[i + 3];

            accumulator ^= iter_data1;
            accumulator ^= iter_data2;
            accumulator ^= iter_data3;
            accumulator ^= iter_data4;

            accumulator *= p2;
            accumulator ^= (accumulator >> 33);
        }

        for (efnhash64_uint_length i = data_length / 4 * 4; i + 1 < data_length; i += 2) {
            efnhash64_block_size iter_data1 = data[i];
            efnhash64_block_size iter_data2 = data[i + 1];

            accumulator ^= iter_data1;
            accumulator ^= iter_data2;

            accumulator *= p3;
            accumulator ^= (accumulator >> 33);
        }

        for (efnhash64_uint_length i = data_length / 2 * 2; i < data_length; i++) {
            efnhash64_block_size iter_data = data[i];

            accumulator ^= iter_data;
            accumulator *= p4;
            accumulator ^= (accumulator >> 33);
        }

        accumulator = (accumulator >> 31) | (accumulator << (64 - 31)) * p1;
        accumulator = (accumulator << 33) | (accumulator >> (64 - 33)) * p3;

        return accumulator;
    }

    inline efnhash64_digest efnhash64_fullcustom(efnhash64_block_size* data, efnhash64_uint_length data_length, efnhash64_uint_64 p1_c, efnhash64_uint_64 p2_c, efnhash64_uint_64 p3_c, efnhash64_uint_64 p4_c, efnhash64_uint_64 accumulator_c) {
        efnhash64_accumulator_size accumulator = accumulator_c;

        accumulator *= data_length;

        for (efnhash64_uint_length i = 0; i + 7 < data_length; i += 8) {
            efnhash64_block_size iter_data1 = data[i];
            efnhash64_block_size iter_data2 = data[i + 1];
            efnhash64_block_size iter_data3 = data[i + 2];
            efnhash64_block_size iter_data4 = data[i + 3];
            efnhash64_block_size iter_data5 = data[i + 4];
            efnhash64_block_size iter_data6 = data[i + 5];
            efnhash64_block_size iter_data7 = data[i + 6];
            efnhash64_block_size iter_data8 = data[i + 7];

            accumulator ^= iter_data1;
            accumulator ^= iter_data2;
            accumulator ^= iter_data3;
            accumulator ^= iter_data4;
            accumulator ^= iter_data5;
            accumulator ^= iter_data6;
            accumulator ^= iter_data7;
            accumulator ^= iter_data8;

            accumulator *= p1_c;
            accumulator ^= (accumulator >> 33);
        }

        for (efnhash64_uint_length i = data_length / 8 * 8; i + 3 < data_length; i += 4) {
            efnhash64_block_size iter_data1 = data[i];
            efnhash64_block_size iter_data2 = data[i + 1];
            efnhash64_block_size iter_data3 = data[i + 2];
            efnhash64_block_size iter_data4 = data[i + 3];

            accumulator ^= iter_data1;
            accumulator ^= iter_data2;
            accumulator ^= iter_data3;
            accumulator ^= iter_data4;

            accumulator *= p2_c;
            accumulator ^= (accumulator >> 33);
        }

        for (efnhash64_uint_length i = data_length / 4 * 4; i + 1 < data_length; i += 2) {
            efnhash64_block_size iter_data1 = data[i];
            efnhash64_block_size iter_data2 = data[i + 1];

            accumulator ^= iter_data1;
            accumulator ^= iter_data2;

            accumulator *= p3_c;
            accumulator ^= (accumulator >> 33);
        }

        for (efnhash64_uint_length i = data_length / 2 * 2; i < data_length; i++) {
            efnhash64_block_size iter_data = data[i];

            accumulator ^= iter_data;
            accumulator *= p4_c;
            accumulator ^= (accumulator >> 33);
        }

        accumulator = (accumulator >> 31) | (accumulator << (64 - 31)) * p1;
        accumulator = (accumulator << 33) | (accumulator >> (64 - 33)) * p3;

        return accumulator;
    }

    inline efnhash64_digest efnhash64_single(efnhash64_block_size data) {
        efnhash64_accumulator_size accumulator = acc_default;

        accumulator ^= data;
        accumulator *= p4;
        accumulator ^= (accumulator >> 33);

        accumulator = (accumulator >> 31) | (accumulator << (64 - 31)) * p1;
        accumulator = (accumulator << 33) | (accumulator >> (64 - 33)) * p3;

        return accumulator;
    }
}
