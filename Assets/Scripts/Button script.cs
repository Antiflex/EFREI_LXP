using Microsoft.MixedReality.Toolkit.Input;
using Microsoft.MixedReality.Toolkit.UI;
using UnityEngine;

namespace Synergiz.Harbor.Player
{
    public class ButtonInteraction : MonoBehaviour
    {
        GameObject cube = null;

        Color[] Colors = { Color.red, Color.black, Color.white, Color.blue, Color.green };
        // Start is called before the first frame update
        void Start()
        {
            CreateCubeOnClick();
        }

        // Update is called once per frame
        void Update()
        {
        
        }

        public void CreateCubeOnClick()
        {
            Debug.Log("Clicked");
            cube = GameObject.CreatePrimitive(PrimitiveType.Cube);
            BoxCollider gameObjectBoxCollider = cube.AddComponent<BoxCollider>();
            cube.AddComponent<ObjectManipulator>();
            cube.AddComponent<NearInteractionGrabbable>();
            Rigidbody gameObjectsRigidBody = cube.AddComponent<Rigidbody>();
            gameObjectsRigidBody.mass = 5;
        }

        public void ChangeCubeColorOnClick()
        {
            if(cube != null)
            {
                cube.GetComponent<MeshRenderer>().material.color = Colors[UnityEngine.Random.Range(0, Colors.Length)];
            }
        }

        public void ToggleCubeColor(string colString)
        {
            ColorUtility.TryParseHtmlString(colString, out Color cubeCol);
            if(cubeCol != null)
            {
                try
                {
                    cube.GetComponent<MeshRenderer>().material.color = cubeCol;
                }catch(UnityException e) { Debug.LogError(e); }
            }
        }
    }
}
