#pragma once
#ifndef QY_FIXED16_16_RAW_HPP
#define QY_FIXED16_16_RAW_HPP

namespace qy {
    namespace fixed16_16_raw {

        const int FP_Int_Digits = 15;
        const int FP_Frac_Digits = 16;
        const int FP_Int_Mask = 0x7fff0000;
        const int FP_Frac_Mask = 0x0000ffff;
        const int FP_Raw_One = 1 << 16;
        const int FP_Raw_Half = 1 << 15;
        const int FP_Raw_Eps = 1;
        const int FP_Raw_Max = 0x7fff;

        typedef int Fixed16_16_raw;
        Fixed16_16_raw toFixed(int n) {
            return n << 16;
        }

        Fixed16_16_raw toFixed(float n) {
            return n * 65536.0f;
        }

        Fixed16_16_raw toFixed(double n) {
            return n * 65536;
        }

        // NOTE floor
        int fixed2int(Fixed16_16_raw n) {
            return n >> 16;
        }
        // 
        int fixed2int_rounding(Fixed16_16_raw n) {
            return (n >> 16) + ((n < 0) && ((n & FP_Frac_Mask) != 0));
        }
        float fixed2float(Fixed16_16_raw n) {
            return n / 65536.0f;
        }
        double fixed2double(Fixed16_16_raw n) {
            return n / 65536.0;
        }
        Fixed16_16_raw floor(Fixed16_16_raw n) {
            return (n & FP_Int_Mask);
        }
        Fixed16_16_raw ceil(Fixed16_16_raw n) {
            return (n & FP_Int_Mask) + FP_Raw_One;
        }
        Fixed16_16_raw round(Fixed16_16_raw n) {
            return (n + FP_Raw_Half) & FP_Int_Mask;
        }
        Fixed16_16_raw multiply(Fixed16_16_raw a, Fixed16_16_raw b) {
            return (int)(((long long)a * (long long)b) >> 16);
        }
        Fixed16_16_raw divide(Fixed16_16_raw a, Fixed16_16_raw b) {
            return (int)(((long long)a << 16) / b);
        }

        Fixed16_16_raw atan2(Fixed16_16_raw y, Fixed16_16_raw x) {

            static const Fixed16_16_raw pi2 = toFixed(6.283185307179586476925286);
            static const Fixed16_16_raw pi = toFixed(3.1415926535897932384626433);
            static const Fixed16_16_raw pi_2 = toFixed(1.5707963267948966192313216);
            static const Fixed16_16_raw pi_4 = toFixed(0.7853981633974483096156608);
            static const Fixed16_16_raw pi_8 = toFixed(0.3926990816987241548078304);

            static const Fixed16_16_raw atan2_p1 = toFixed(0.9997878412794807);
            static const Fixed16_16_raw atan2_p3 = toFixed(-0.3258083974640975);
            static const Fixed16_16_raw atan2_p5 = toFixed(0.1555786518463281);
            static const Fixed16_16_raw atan2_p7 = toFixed(-0.04432655554792128);

            Fixed16_16_raw ay = y < 0 ? -y : y;
            Fixed16_16_raw ax = x < 0 ? -x : x;

            Fixed16_16_raw ans, c, c2;

            if (ax >= ay) {
                c = divide(ay, ax + FP_Raw_Eps);
                c2 = multiply(c, c);
                ans = multiply(c, atan2_p1 + multiply(c2, atan2_p3 + multiply(c2, atan2_p5 + multiply(c2, atan2_p7))));
            }
            else {
                c = divide(ax, ay + FP_Raw_Eps);
                c2 = multiply(c, c);
                ans = pi_4 - multiply(c, atan2_p1 + multiply(c2, atan2_p3 + multiply(c2, atan2_p5 + multiply(c2, atan2_p7))));
            }
            if (x < 0)
                ans = pi - ans;
            if (y < 0)
                ans = pi2 - ans;
            return ans;
        }

    }
}

#endif
