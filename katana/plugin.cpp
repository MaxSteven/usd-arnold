//.#include "pxrUsdInShipped/declareCoreOps.h"


#include <usdKatana/attrMap.h>
#include <usdKatana/usdInPluginRegistry.h>

#include <pxr/usd/usdAi/aiProcedural.h>
#include <pxr/usd/usdAi/aiVolume.h>

#include "readProcedural.h"
#include "readPrim.h"

PXR_NAMESPACE_USING_DIRECTIVE

PXRUSDKATANA_USDIN_PLUGIN_DECLARE(AiProceduralOp)

PXRUSDKATANA_USDIN_PLUGIN_DEFINE(AiProceduralOp, privateData, interface)
{
    PxrUsdKatanaAttrMap attrs;

    ReadAiProcedural(
        UsdAiProcedural(privateData.GetUsdPrim()), privateData, attrs);

    attrs.toInterface(interface);
}

DEFINE_GEOLIBOP_PLUGIN(AiProceduralOp)

void registerPlugins()
{
    REGISTER_PLUGIN(AiProceduralOp, "AiProceduralOp", 0, 1);

    PxrUsdKatanaUsdInPluginRegistry::RegisterUsdType<UsdAiProcedural>("AiProceduralOp");
    PxrUsdKatanaUsdInPluginRegistry::RegisterUsdType<UsdAiVolume>("AiProceduralOp");

    PxrUsdKatanaUsdInPluginRegistry::RegisterLocationDecoratorFnc(readPrimLocation);
}
