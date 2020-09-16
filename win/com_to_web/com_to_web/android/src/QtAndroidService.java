import android.content.Context;
import android.content.Intent;
import android.util.Log;
import org.qtproject.qt5.android.bindings.QtService;


public class QtAndroidService extends QtService
{
    public static void startQtAndroidService(Context context) {
            context.startService(new Intent(context, QtAndroidService.class));
    }
}
