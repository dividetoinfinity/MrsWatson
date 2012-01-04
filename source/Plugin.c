//
//  Plugin.c
//  MrsWatson
//
//  Created by Nik Reiman on 1/3/12.
//  Copyright (c) 2012 Teragon Audio. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "Plugin.h"
#include "EventLogger.h"
#include "PluginVst2x.h"

PluginType guessPluginType(CharString pluginName) {
  PluginType pluginType = PLUGIN_TYPE_INVALID;
  logDebug("Trying to find plugin '%s'", pluginName->data);

  if(vst2xPluginExists(pluginName)) {
    logInfo("Plugin '%s' is of type VST2.x", pluginName->data);
    pluginType = PLUGIN_TYPE_VST_2X;
  }
  else {
    logError("Plugin '%s' could not be found", pluginName->data);
  }

  return pluginType;
}

Plugin newPlugin(PluginType pluginType, const CharString pluginName) {
  switch(pluginType) {
    case PLUGIN_TYPE_VST_2X:
      return newPluginVst2x(pluginName);
    case PLUGIN_TYPE_INVALID:
    default:
      logError("Plugin type not supported");
      return NULL;
  }
}

void freePlugin(Plugin plugin) {
  plugin->freePluginData(plugin->extraData);
  freeCharString(plugin->pluginName);
  free(plugin);
}
