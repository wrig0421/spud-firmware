#if !defined(SERIAL_COM_H)
#define SERIAL_COM_H

void task_sensor_tx_entry(void *argument);
void sensor_rx_entry(void *argument);
void serial_com_init_all(void);
bool pkt_received(void);
void clear_pkt_received_flag(void);
bool pkt_received(void);

#endif
