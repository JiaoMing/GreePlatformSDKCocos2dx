#include "CCWebView.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxWebView.h"

namespace cocos2d { namespace webview_plugin {

CCWebViewDelegate *CCWebView::s_pWebViewDelegate = NULL;

CCWebView::CCWebView(void* obj){
	mWebView = obj;
}

CCWebView* CCWebView::create(){
	jobject obj = createWebViewJni();
	CCWebView* webview = NULL;
	if(obj != NULL){
		webview = new CCWebView((void*)obj);
		setJavascriptIfJni(obj, webview);	
		webview->autorelease();
		webview->retain();
	}
	return webview;
}

void CCWebView::loadUrl(const char* url){
	if(mWebView != NULL){
		loadUrlJni((jobject)mWebView, url);
	}
}

void CCWebView::evaluateJS(const char* js){
	if(mWebView != NULL){
		evaluateJSJni((jobject)mWebView, js);
	}
}

void CCWebView::setVisibility(bool enable){
	if(mWebView != NULL){
		setVisibilityJni((jobject)mWebView, enable);
	}
}

void CCWebView::setRect(int x, int y, int w, int h){
	if(mWebView != NULL){
		setRectJni((jobject)mWebView, x, y, w, h);
	}
}

void CCWebView::destroy(){
	if(mWebView != NULL){
		destroyJni((jobject)mWebView);
	}
}


void CCWebView::handleCalledFromJS(const char *message){
	CCWebViewDelegate *delegate = CCWebView::getWebViewDelegate();
	if(delegate != NULL){
		CCString *str = new CCString(message);
		str->autorelease();
		delegate->callbackFromJS(this, str);
	}
}

}} // End of namespae cocos2d::webview_plugin
