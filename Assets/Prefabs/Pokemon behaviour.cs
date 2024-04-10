using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Synergiz.Harbor.Player
{
    public class Pokemonbehaviour : MonoBehaviour
    {
        public const float SCALING_DURATION = 1;
        private Coroutine scaleCoroutine;
        public float catchProbabilty = 0.5f;
        public bool isHitByPokeball = false;
        public bool isCaught = false;

        // Start is called before the first frame update
        void Start()
        {
        
        }

        // Update is called once per frame
        void Update()
        {
        
        }

        private void OnCollisionEnter(Collision collision)
        {
            Debug.Log("Pokemon is hit!");
            Pokeballbehaviour pokeballbehaviour = collision.gameObject.GetComponent<Pokeballbehaviour>();
            if (pokeballbehaviour is not null)
            {
                Debug.Log("By a pokeball");
                GameObject pokeball = collision.gameObject;
                if (pokeballbehaviour.isThrown && !pokeballbehaviour.hasHitPokemon && !pokeballbehaviour.hasHitHazard)
                {
                    this.triggerCatchingPhase(pokeball, pokeballbehaviour);
                    pokeballbehaviour.triggerCatchingphase(this.gameObject);
                }
            }
        }

        private void triggerCatchingPhase(GameObject pokeball, Pokeballbehaviour pokeballAttributes)
        {
            if (scaleCoroutine is not null)
                StopCoroutine(scaleCoroutine);

            scaleCoroutine = StartCoroutine(ScaleObject(Vector3.zero, SCALING_DURATION));
        }

        private IEnumerator ScaleObject(Vector3 targetScale, float duration)
        {
            float timer = 0f;
            Vector3 startScale = transform.localScale;

            while (timer < duration)
            {
                transform.localScale = Vector3.Lerp(startScale, targetScale, timer / duration);
                timer += Time.deltaTime;
                yield return null;
            }

            // Ensure final scale is set exactly to target scale
            transform.localScale = targetScale;
        }
    }
}
