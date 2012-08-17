package aop.control;

import android.app.TabActivity;
import android.content.Intent;
import android.content.res.Resources;
import android.os.Bundle;
import android.widget.TabHost;
import aop.command.CommandControl;
import aop.status.StatusControl;

public class Control extends TabActivity {

    public static int svSetting = 0;
    public static int ffSetting = 0;   
    public static boolean connectFF = false;
    public static CommandControl cmct = new CommandControl();
    public static StatusControl stct = new StatusControl();
    public static boolean whileCommand = true;
    public static boolean whileStatus = true;
    
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        Resources res = getResources();  // Resource object to get Drawables
        TabHost tabHost = getTabHost();  // The activity TabHost
        TabHost.TabSpec spec;            // Resusable TabSpec for each tab
        Intent intent;                   // Reusable Intent for each tab

        // Create an Intent to launch an Activity for the tab (to be reused)
        intent = new Intent().setClass(this, SettingActivity.class);

        // Initialize a TabSpec for each tab and add it to the TabHost
        spec = tabHost.newTabSpec("setting").setIndicator("Setting",
                res.getDrawable(R.drawable.ic_tab_setting))
                .setContent(intent);
        tabHost.addTab(spec);

        // Do the same for the other tabs
        intent = new Intent().setClass(this, ControlActivity.class);
        spec = tabHost.newTabSpec("control").setIndicator("Control",
                res.getDrawable(R.drawable.ic_tab_control))
                .setContent(intent);
        tabHost.addTab(spec);
        tabHost.setCurrentTab(0);
    }
}