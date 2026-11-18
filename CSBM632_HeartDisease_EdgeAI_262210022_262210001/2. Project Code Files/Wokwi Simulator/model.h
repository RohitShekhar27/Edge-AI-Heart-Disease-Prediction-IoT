#pragma once
#include <cstdarg>
namespace Eloquent {
    namespace ML {
        namespace Port {
            class LogisticRegression {
                public:
                    /**
                    * Predict class for features vector
                    */
                    int predict(float *x) {
                        float votes[2] = { -4.4855497e-05  };
                        votes[0] += dot(x,   0.009721788577  , -1.292527325886  , 0.889066194343  , -0.012080586358  , -0.002581249377  , -0.074135189359  , 0.5778861684  , 0.034029045392  , -0.902540480864  , -0.492049787233  , 0.242350960953  , -0.793808122416  , -1.160355727679 );
                        // return argmax of votes
                        uint8_t classIdx = 0;
                        float maxVotes = votes[0];

                        for (uint8_t i = 1; i < 2; i++) {
                            if (votes[i] > maxVotes) {
                                classIdx = i;
                                maxVotes = votes[i];
                            }
                        }

                        return classIdx;
                    }

                protected:
                    /**
                    * Compute dot product
                    */
                    float dot(float *x, ...) {
                        va_list w;
                        va_start(w, 13);
                        float dot = 0.0;

                        for (uint16_t i = 0; i < 13; i++) {
                            const float wi = va_arg(w, double);
                            dot += x[i] * wi;
                        }

                        return dot;
                    }
                };
            }
        }
    }