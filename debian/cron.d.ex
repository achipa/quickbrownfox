#
# Regular cron jobs for the appwatch package
#
0 4	* * *	root	[ -x /usr/bin/appwatch_maintenance ] && /usr/bin/appwatch_maintenance
