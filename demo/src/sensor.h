#ifdef __cplusplus 
extern "C" {
#endif

void* CreateSensor();
int GetSensorValue(void* sensor);
void DestroySensor(void* sensor);

#ifdef __cplusplus 
}
#endif