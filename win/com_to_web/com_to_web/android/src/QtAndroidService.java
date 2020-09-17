import android.content.Context;
import android.content.Intent;
import android.util.Log;
import org.qtproject.qt5.android.bindings.QtService;

public class QtAndroidService extends QtService
{
    private static final String TAG = "QtAndroidService";

    @Override
    public void onCreate() {
        super.onCreate();
        Log.i(TAG, "Creating Service");
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        Log.i(TAG, "Destroying Service");
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        int ret = super.onStartCommand(intent, flags, startId);

        // Do some work

        return ret;
    }

    public static void startQtAndroidService(Context context) {
        Log.i(TAG, "Hey");
       /* Notification.Builder builder = new Notification.Builder(context, ChannelId)
                                .setContentTitle("Test Service")
                                .setContentText(message)
                                .setSmallIcon(android.R.drawable.ic_media_play)
                                .setOngoing(true);

                        context.startForeground(NotId, builder.build());*/
            //context.startService(new Intent(context, QtAndroidService.class));
            context.startForegroundService(new Intent(context, QtAndroidService.class));
    }
}
