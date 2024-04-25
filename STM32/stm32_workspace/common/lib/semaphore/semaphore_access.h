/*
 * semaphore.h
 *
 *  Created on: Nov 12, 2022
 *      Author: spud
 */

#ifndef SEMAPHORE_ACCESS_H
#define SEMAPHORE_ACCESS_H

typedef enum
{
	SEMAPHORE_DMA_TRANSFER,
	NUM_SEMAPHORES
} semaphore_assignment_e;


void semaphore_create(void);
void semaphore_take(semaphore_assignment_e semaphore);
void semaphore_give(semaphore_assignment_e semaphore);

#endif /* SEMAPHORE_ACCESS_H */
