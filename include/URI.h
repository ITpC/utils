#ifndef __URI_H__
#define

#include <string>

class URI
{
private:
    struct URI_SchemeSpecific
    {
        std::string mAuthority;
        std::string mUserInfo;
        std::string mHost;
        int         mPort;
        std::string mPath;
        std::string mQuery;

        
        bool mHasAuthority;
        bool mHasUserInfo;
        bool mHasHost;
        bool mHasPort;
        bool mHasPath;
        bool mHasQuery;
        
        explicit URI_SchemeSpecific(const std::string& ref)
        {
            parse(ref);
        }
        
    };
    
    std::string         mFullURI;
    std::string         mScheme;
    URI_SchemeSpecific  mSSP;
    std::string         mFragment;
    bool                mIsOpaque;
    bool                mIsHierarhical;
    
public:
    
};


#endif /* __URI_H__ */
