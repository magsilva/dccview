#include <kudzu/kudzu.h>
#include <stdio.h>

/*
 * To compile it type:
 * gcc monitor_detect.c -o monitor_detect.out -lkudzu -lpci -static
*/
int main () {
	int i=0;
	struct ddcDevice *monitor = NULL;
	struct device **hw;
	//char buf[128];
	char buf[1024];

	initializeDeviceList();

	printf ("Detecting your monitor...\n");
	hw = probeDevices(CLASS_MONITOR, BUS_DDC, PROBE_ONE);

	if (hw == NULL || ((monitor = *(struct ddcDevice**)hw) == NULL &&
	    (monitor = (struct ddcDevice*)ddcProbe(CLASS_MONITOR,
						   PROBE_ONE, NULL)) == NULL)) {
		printf("No DDC capable monitor detected!\n");
		return -1;
	}

	if ((monitor->horizSyncMin == 0) || (monitor->horizSyncMax == 0) || (monitor->vertRefreshMin == 0) || (monitor->vertRefreshMax == 0)) {
		printf("No DDC capable monitor detected!!!!\nhorizSyncMin = %d \nhorizSyncMax = %d \nvertRefreshMin = %d \nvertRefreshMax = %d \n",
				                     monitor->horizSyncMin, monitor->horizSyncMax, monitor->vertRefreshMin, monitor->vertRefreshMax);
		return -1;
	}
	
	printf("Monitor id: %s\n HSync: %d - %d\n VRefresh: %d - %d\n",
			monitor->id, monitor->horizSyncMin, monitor->horizSyncMax, monitor->vertRefreshMin, monitor->vertRefreshMax);

	printf("Begin if 'Monitor modes':\n'");
	for (i = 0; monitor->modes[i]; i += 2) {
		if (i) {
			printf(" ");
		}
		printf("%dx%d", monitor->modes[i], monitor->modes[i + 1]);
	}
	printf("'\n");
	printf("End of 'Monitor modes'.\n");
	
	printf("Contents of buf array:\n");
	sprintf(buf, "%s (", monitor->id);
	for (i = 0; monitor->modes[i]; i += 2) {
		if (i) {
			strcat(buf, " ");
		}
		sprintf(buf + strlen(buf), "%dx%d",
				monitor->modes[i], monitor->modes[i + 1]);
		printf("DEBUG buf = '%s'\n", buf);
	}
	strcat(buf, ")");
	printf("buf array = '%s'\n", buf);
	printf("buf size = '%d'\n", strlen(buf)+1);
	return 0;
}
