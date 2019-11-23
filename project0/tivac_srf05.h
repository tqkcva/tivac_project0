/*
 * tivac_srf05.h
 *
 *  Created on: Nov 23, 2019
 *      Author: tqkieu
 */

#ifndef TIVAC_SRF05_H_
#define TIVAC_SRF05_H_

/**
 * GPIO interrupt will be used
 */
int srf05_init(void);
int srf05_deinit(void);
int srf05_get_distance(void);

#endif /* TIVAC_SRF05_H_ */
